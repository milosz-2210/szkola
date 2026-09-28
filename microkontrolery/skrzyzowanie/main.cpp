// ===============================
// NORMALNE SKRZYŻOWANIE
// ===============================

// CZASY
#define CZERWONE 2000
#define ZIELONE 4000


// KIERUNEK 1
#define ZIELONA1 7
#define CZERWONA1 6

// KIERUNEK 2
#define ZIELONA2 5
#define CZERWONA2 4

// KIERUNEK 3
#define ZIELONA3 A4
#define CZERWONA3 A3

// KIERUNEK 4
#define ZIELONA4 A2
#define CZERWONA4 A1


// Czas ostatniej zmiany
unsigned long poprzedniCzas = 0;

// Aktualny etap
int etap = 0;


void setup()
{
  pinMode(ZIELONA1, OUTPUT);
  pinMode(CZERWONA1, OUTPUT);

  pinMode(ZIELONA2, OUTPUT);
  pinMode(CZERWONA2, OUTPUT);

  pinMode(ZIELONA3, OUTPUT);
  pinMode(CZERWONA3, OUTPUT);

  pinMode(ZIELONA4, OUTPUT);
  pinMode(CZERWONA4, OUTPUT);
}


void loop()
{
  unsigned long aktualnyCzas = millis();


  // ===============================
  // ETAP 0
  // Wszystkie czerwone - 2 sekundy
  // ===============================

  if (etap == 0 && aktualnyCzas - poprzedniCzas >= CZERWONE)
  {
    poprzedniCzas = aktualnyCzas;
    etap = 1;
  }


  // ===============================
  // ETAP 1
  // Zielona 1 - 4 sekundy
  // ===============================

  if (etap == 1 && aktualnyCzas - poprzedniCzas >= ZIELONE)
  {
    poprzedniCzas = aktualnyCzas;
    etap = 2;
  }


  // ===============================
  // ETAP 2
  // Wszystkie czerwone - 2 sekundy
  // ===============================

  if (etap == 2 && aktualnyCzas - poprzedniCzas >= CZERWONE)
  {
    poprzedniCzas = aktualnyCzas;
    etap = 3;
  }


  // ===============================
  // ETAP 3
  // Zielona 2 - 4 sekundy
  // ===============================

  if (etap == 3 && aktualnyCzas - poprzedniCzas >= ZIELONE)
  {
    poprzedniCzas = aktualnyCzas;
    etap = 4;
  }


  // ===============================
  // ETAP 4
  // Wszystkie czerwone - 2 sekundy
  // ===============================

  if (etap == 4 && aktualnyCzas - poprzedniCzas >= CZERWONE)
  {
    poprzedniCzas = aktualnyCzas;
    etap = 5;
  }


  // ===============================
  // ETAP 5
  // Zielona 3 - 4 sekundy
  // ===============================

  if (etap == 5 && aktualnyCzas - poprzedniCzas >= ZIELONE)
  {
    poprzedniCzas = aktualnyCzas;
    etap = 6;
  }


  // ===============================
  // ETAP 6
  // Wszystkie czerwone - 2 sekundy
  // ===============================

  if (etap == 6 && aktualnyCzas - poprzedniCzas >= CZERWONE)
  {
    poprzedniCzas = aktualnyCzas;
    etap = 7;
  }


  // ===============================
  // ETAP 7
  // Zielona 4 - 4 sekundy
  // ===============================

  if (etap == 7 && aktualnyCzas - poprzedniCzas >= ZIELONE)
  {
    poprzedniCzas = aktualnyCzas;
    etap = 0;
  }


  // ===============================
  // USTAWIENIA ŚWIATEŁ
  // ===============================


  // ETAP 0
  // Wszystkie czerwone

  if (etap == 0)
  {
    digitalWrite(ZIELONA1, LOW);
    digitalWrite(CZERWONA1, HIGH);

    digitalWrite(ZIELONA2, LOW);
    digitalWrite(CZERWONA2, HIGH);

    digitalWrite(ZIELONA3, LOW);
    digitalWrite(CZERWONA3, HIGH);

    digitalWrite(ZIELONA4, LOW);
    digitalWrite(CZERWONA4, HIGH);
  }


  // ETAP 1
  // Zielona 1

  if (etap == 1)
  {
    digitalWrite(ZIELONA1, HIGH);
    digitalWrite(CZERWONA1, LOW);

    digitalWrite(ZIELONA2, LOW);
    digitalWrite(CZERWONA2, HIGH);

    digitalWrite(ZIELONA3, LOW);
    digitalWrite(CZERWONA3, HIGH);

    digitalWrite(ZIELONA4, LOW);
    digitalWrite(CZERWONA4, HIGH);
  }


  // ETAP 2
  // Wszystkie czerwone

  if (etap == 2)
  {
    digitalWrite(ZIELONA1, LOW);
    digitalWrite(CZERWONA1, HIGH);

    digitalWrite(ZIELONA2, LOW);
    digitalWrite(CZERWONA2, HIGH);

    digitalWrite(ZIELONA3, LOW);
    digitalWrite(CZERWONA3, HIGH);

    digitalWrite(ZIELONA4, LOW);
    digitalWrite(CZERWONA4, HIGH);
  }


  // ETAP 3
  // Zielona 2

  if (etap == 3)
  {
    digitalWrite(ZIELONA1, LOW);
    digitalWrite(CZERWONA1, HIGH);

    digitalWrite(ZIELONA2, HIGH);
    digitalWrite(CZERWONA2, LOW);

    digitalWrite(ZIELONA3, LOW);
    digitalWrite(CZERWONA3, HIGH);

    digitalWrite(ZIELONA4, LOW);
    digitalWrite(CZERWONA4, HIGH);
  }


  // ETAP 4
  // Wszystkie czerwone

  if (etap == 4)
  {
    digitalWrite(ZIELONA1, LOW);
    digitalWrite(CZERWONA1, HIGH);

    digitalWrite(ZIELONA2, LOW);
    digitalWrite(CZERWONA2, HIGH);

    digitalWrite(ZIELONA3, LOW);
    digitalWrite(CZERWONA3, HIGH);

    digitalWrite(ZIELONA4, LOW);
    digitalWrite(CZERWONA4, HIGH);
  }


  // ETAP 5
  // Zielona 3

  if (etap == 5)
  {
    digitalWrite(ZIELONA1, LOW);
    digitalWrite(CZERWONA1, HIGH);

    digitalWrite(ZIELONA2, LOW);
    digitalWrite(CZERWONA2, HIGH);

    digitalWrite(ZIELONA3, HIGH);
    digitalWrite(CZERWONA3, LOW);

    digitalWrite(ZIELONA4, LOW);
    digitalWrite(CZERWONA4, HIGH);
  }


  // ETAP 6
  // Wszystkie czerwone

  if (etap == 6)
  {
    digitalWrite(ZIELONA1, LOW);
    digitalWrite(CZERWONA1, HIGH);

    digitalWrite(ZIELONA2, LOW);
    digitalWrite(CZERWONA2, HIGH);

    digitalWrite(ZIELONA3, LOW);
    digitalWrite(CZERWONA3, HIGH);

    digitalWrite(ZIELONA4, LOW);
    digitalWrite(CZERWONA4, HIGH);
  }


  // ETAP 7
  // Zielona 4

  if (etap == 7)
  {
    digitalWrite(ZIELONA1, LOW);
    digitalWrite(CZERWONA1, HIGH);

    digitalWrite(ZIELONA2, LOW);
    digitalWrite(CZERWONA2, HIGH);

    digitalWrite(ZIELONA3, LOW);
    digitalWrite(CZERWONA3, HIGH);

    digitalWrite(ZIELONA4, HIGH);
    digitalWrite(CZERWONA4, LOW);
  }
}
