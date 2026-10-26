
 // =========================================
// SKRZYZOWANIE Z 4 CZUJNIKAMI PIR
// Kolejka kierunkow wedlug wykrycia ruchu
// =========================================

// CZASY
#define CZERWONE 2000UL
#define ZIELONE  4000UL

// KIERUNEK 1
#define CZERWONA1 4
#define ZIELONA1  5
#define CZUJNIK1  2

// KIERUNEK 2
#define CZERWONA2 6
#define ZIELONA2  7
#define CZUJNIK2  3

// KIERUNEK 3
#define CZERWONA3 A1
#define ZIELONA3  A2
#define CZUJNIK3  A0

// KIERUNEK 4
#define CZERWONA4 A3
#define ZIELONA4  A4
#define CZUJNIK4  A5

// Maksymalna liczba oczekujacych kierunkow
const byte ROZMIAR_KOLEJKI = 4;

// Kolejka kierunkow: 1, 2, 3, 4
byte kolejka[ROZMIAR_KOLEJKI];
byte poczatek = 0;
byte koniec = 0;
byte liczbaWKolejce = 0;

// Poprzedni stan czujnikow
bool poprzedniStan[4] = {LOW, LOW, LOW, LOW};

// Etapy:
// 0 - oczekiwanie na ruch
// 1 - zielone swiatlo
// 2 - wszystkie czerwone
byte etap = 0;
byte aktywnyKierunek = 0;

unsigned long poprzedniCzas = 0;

// =========================================
// USTAWIANIE SWIATEL
// =========================================

void wszystkieCzerwone()
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

void ustawZielone(byte kierunek)
{
  wszystkieCzerwone();

  switch (kierunek)
  {
    case 1:
      digitalWrite(CZERWONA1, LOW);
      digitalWrite(ZIELONA1, HIGH);
      break;

    case 2:
      digitalWrite(CZERWONA2, LOW);
      digitalWrite(ZIELONA2, HIGH);
      break;

    case 3:
      digitalWrite(CZERWONA3, LOW);
      digitalWrite(ZIELONA3, HIGH);
      break;

    case 4:
      digitalWrite(CZERWONA4, LOW);
      digitalWrite(ZIELONA4, HIGH);
      break;
  }
}

// =========================================
// DODAWANIE KIERUNKU DO KOLEJKI
// =========================================

void dodajDoKolejki(byte kierunek)
{
  // Nie dodawaj kierunku, ktory juz czeka
  // ani kierunku aktualnie obslugiwanego.
  if (kierunek == aktywnyKierunek)
    return;

  for (byte i = 0; i < liczbaWKolejce; i++)
  {
    byte indeks = (poczatek + i) % ROZMIAR_KOLEJKI;

    if (kolejka[indeks] == kierunek)
      return;
  }

  // Kolejka moze pomiescic 4 rozne kierunki
  if (liczbaWKolejce < ROZMIAR_KOLEJKI)
  {
    kolejka[koniec] = kierunek;
    koniec = (koniec + 1) % ROZMIAR_KOLEJKI;
    liczbaWKolejce++;
  }
}

// =========================================
// ODCZYT CZUJNIKOW
// =========================================

void sprawdzCzujniki()
{
  const byte pinyCzujnikow[4] =
  {
    CZUJNIK1, CZUJNIK2, CZUJNIK3, CZUJNIK4
  };

  for (byte i = 0; i < 4; i++)
  {
    bool stan = digitalRead(pinyCzujnikow[i]);

    // Reaguj tylko na nowe wykrycie ruchu
    if (stan == HIGH && poprzedniStan[i] == LOW)
    {
      dodajDoKolejki(i + 1);
    }

    poprzedniStan[i] = stan;
  }
}

// =========================================
// URUCHOMIENIE NASTEPNEGO KIERUNKU
// =========================================

void uruchomNastepnyKierunek(unsigned long teraz)
{
  if (liczbaWKolejce == 0)
  {
    aktywnyKierunek = 0;
    etap = 0;
    wszystkieCzerwone();
    return;
  }

  aktywnyKierunek = kolejka[poczatek];
  poczatek = (poczatek + 1) % ROZMIAR_KOLEJKI;
  liczbaWKolejce--;

  ustawZielone(aktywnyKierunek);

  poprzedniCzas = teraz;
  etap = 1;
}

// =========================================
// SETUP
// =========================================

void setup()
{
  pinMode(CZERWONA1, OUTPUT);
  pinMode(ZIELONA1, OUTPUT);
  pinMode(CZERWONA2, OUTPUT);
  pinMode(ZIELONA2, OUTPUT);
  pinMode(CZERWONA3, OUTPUT);
  pinMode(ZIELONA3, OUTPUT);
  pinMode(CZERWONA4, OUTPUT);
  pinMode(ZIELONA4, OUTPUT);

  pinMode(CZUJNIK1, INPUT);
  pinMode(CZUJNIK2, INPUT);
  pinMode(CZUJNIK3, INPUT);
  pinMode(CZUJNIK4, INPUT);

  wszystkieCzerwone();
}

// =========================================
// GLOWNA PETLA
// =========================================

void loop()
{
  unsigned long teraz = millis();

  // Sprawdzaj wszystkie czujniki przez caly czas
  sprawdzCzujniki();

  // ETAP 0: oczekiwanie na ruch
  if (etap == 0)
  {
    if (liczbaWKolejce > 0)
    {
      uruchomNastepnyKierunek(teraz);
    }
  }

  // ETAP 1: zielone swiatlo przez 4 sekundy
  else if (etap == 1)
  {
    if (teraz - poprzedniCzas >= ZIELONE)
    {
      wszystkieCzerwone();
      poprzedniCzas = teraz;
      etap = 2;
    }
  }

  // ETAP 2: wszystkie czerwone przez 2 sekundy
  else if (etap == 2)
  {
    if (teraz - poprzedniCzas >= CZERWONE)
    {
      // Jesli ktos czeka, obsluz nastepny kierunek
      if (liczbaWKolejce > 0)
      {
        uruchomNastepnyKierunek(teraz);
      }
      else
      {
        aktywnyKierunek = 0;
        etap = 0;
      }
    }
  }
}
