
#include <Servo.h>
#include <IRremote.hpp>

// STANY BRAMY
#define ST_ZAMKNIETA 1
#define ST_OTWIERA 2
#define ST_OTWARTA 3
#define ST_ZAMYKA 4
#define ST_UCHYLONA_ZAMKNIETA 5
#define ST_UCHYLONA_OTWARTA 6

// KOD PILOTA
#define PILOT_OTWORZ 0x10

// PINY
#define SERWO1 A0
#define SERWO2 A1
#define IR_PIN 11
#define LED 7
#define PIR 6

// CZASY
#define CZAS_PELNEGO_RUCHU 10000UL
#define CZAS_MIGANIA 300UL

Servo brama1;
Servo brama2;

uint8_t state = ST_OTWARTA;

float aktualnyKat = 0;
float katStart = 0;
float katCel = 0;

unsigned long czasStart = 0;
unsigned long czasRuchu = 0;
unsigned long czasLED = 0;

bool stanLED = false;


// ROZPOCZECIE RUCHU
void rozpocznijRuch(int cel) {

  if (cel == (int)aktualnyKat) return;

  katStart = aktualnyKat;
  katCel = cel;

  czasStart = millis();

  czasRuchu =
    (unsigned long)(
      abs((int)katCel - (int)katStart)
      * CZAS_PELNEGO_RUCHU / 90
    );

  if (katCel < katStart) {
    state = ST_OTWIERA;
    Serial.println("OTWIERANIE OBU BRAM");
  }
  else {
    state = ST_ZAMYKA;
    Serial.println("ZAMYKANIE OBU BRAM");
  }
}


// ZAKONCZENIE RUCHU
void zakonczRuch() {

  aktualnyKat = katCel;

  if (aktualnyKat >= 90) {
    aktualnyKat = 90;
    state = ST_ZAMKNIETA;
    Serial.println("BRAMY ZAMKNIETE");
  }
  else if (aktualnyKat <= 0) {
    aktualnyKat = 0;
    state = ST_OTWARTA;
    Serial.println("BRAMY OTWARTE");
  }

  digitalWrite(LED, LOW);
  stanLED = false;
}


// ZATRZYMANIE OBU BRAM
void zatrzymajBrame() {

  unsigned long uplynelo = millis() - czasStart;

  float postep = (float)uplynelo / czasRuchu;

  if (postep > 1.0) postep = 1.0;

  aktualnyKat =
    katStart + (katCel - katStart) * postep;

  if (aktualnyKat < 0) aktualnyKat = 0;
  if (aktualnyKat > 90) aktualnyKat = 90;

  brama1.write((int)(aktualnyKat + 0.5));
  brama2.write((int)(aktualnyKat + 0.5));

  // ZAPAMIETANIE KIERUNKU ZATRZYMANIA
  if (state == ST_OTWIERA) {
    state = ST_UCHYLONA_ZAMKNIETA;
    Serial.println("BRAMA ZATRZYMANA PODCZAS OTWIERANIA");
  }
  else if (state == ST_ZAMYKA) {
    state = ST_UCHYLONA_OTWARTA;
    Serial.println("BRAMA ZATRZYMANA PODCZAS ZAMYKANIA");
  }

  katCel = aktualnyKat;
  katStart = aktualnyKat;

  digitalWrite(LED, LOW);
  stanLED = false;
}


// OBSLUGA PIR
// PIR DZIALA TYLKO PODCZAS ZAMYKANIA
void obslugaPIR() {

  if (digitalRead(PIR) == HIGH) {

    if (state == ST_ZAMYKA) {

      zatrzymajBrame();

      Serial.println("PIR - OBIE BRAMY ZATRZYMANE");
    }
  }
}


// OBSLUGA PILOTA
void pilot() {

  if (IrReceiver.decode()) {

    if (!(IrReceiver.decodedIRData.flags &
          IRDATA_FLAGS_IS_REPEAT)) {

      uint8_t kod =
        IrReceiver.decodedIRData.command;

      if (kod == PILOT_OTWORZ) {

        // ZATRZYMANIE PODCZAS RUCHU
        if (state == ST_OTWIERA ||
            state == ST_ZAMYKA) {

          zatrzymajBrame();
        }

        // BRAMY OTWARTE - ZAMYKANIE
        else if (state == ST_OTWARTA) {

          rozpocznijRuch(90);
        }

        // BRAMY ZAMKNIETE - OTWIERANIE
        else if (state == ST_ZAMKNIETA) {

          rozpocznijRuch(0);
        }

        // ZATRZYMANE PODCZAS OTWIERANIA - ZAMYKANIE
        else if (state == ST_UCHYLONA_ZAMKNIETA) {

          rozpocznijRuch(90);
        }

        // ZATRZYMANE PODCZAS ZAMYKANIA - OTWIERANIE
        else if (state == ST_UCHYLONA_OTWARTA) {

          rozpocznijRuch(0);
        }
      }
    }

    IrReceiver.resume();
  }
}


// STEROWANIE OBIEMA BRAMAMI
void sterowanieBrama() {

  if (state == ST_OTWIERA ||
      state == ST_ZAMYKA) {

    unsigned long uplynelo = millis() - czasStart;

    if (uplynelo >= czasRuchu) {

      zakonczRuch();
    }
    else {

      float postep =
        (float)uplynelo / czasRuchu;

      aktualnyKat =
        katStart + (katCel - katStart) * postep;
    }

    int pozycja = (int)(aktualnyKat + 0.5);

    brama1.write(pozycja);
    brama2.write(pozycja);
  }
}


// MIGANIE LED
void miganieLED() {

  if (state == ST_OTWIERA ||
      state == ST_ZAMYKA) {

    if (millis() - czasLED >= CZAS_MIGANIA) {

      czasLED = millis();
      stanLED = !stanLED;

      digitalWrite(LED, stanLED);
    }
  }
  else {

    digitalWrite(LED, LOW);
    stanLED = false;
  }
}


// SETUP
void setup() {

  Serial.begin(9600);

  brama1.attach(SERWO1);
  brama2.attach(SERWO2);

  // POZYCJA POCZATKOWA - OTWARTA
  brama1.write(0);
  brama2.write(0);

  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);

  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

  state = ST_OTWARTA;

  Serial.println("STEROWNIK DWÓCH BRAM GOTOWY");
}


// LOOP
void loop() {

  obslugaPIR();

  pilot();

  sterowanieBrama();

  miganieLED();
}
