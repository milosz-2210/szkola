// C++ code
//
// Definiowanie pinów, do których podłączone są diody LED
const int ledgreen1 = 8;
const int ledred1 = 9;
const int ledgreen2 = 10;
const int ledred2 = 11;

// Zmienna przechowująca czas wykonania ostatniej zmiany etapu
unsigned long poprzedniCzas = 0;

// Zmienna określająca aktualny etap działania świateł
int etap = 0;

void setup()
{
  // Ustawienie wszystkich pinów jako wyjścia
  pinMode(ledgreen1, OUTPUT);
  pinMode(ledred1, OUTPUT);
  pinMode(ledgreen2, OUTPUT);
  pinMode(ledred2, OUTPUT);
}

void loop()
{
  // Pobranie aktualnego czasu od uruchomienia programu
  unsigned long aktualnyCzas = millis();
  
   // ETAP 0
   // Ten etap trwa 4 sekundy
  if(etap == 0 && aktualnyCzas - poprzedniCzas >= 4000)
  {
    // Zapamiętanie aktualnego czasu
    poprzedniCzas = aktualnyCzas;
    // Przejście do etapu 1
    etap = 1;
  }
  // ETAP 1
  // Ten etap trwa 2 sekundy
  if(etap == 1 && aktualnyCzas - poprzedniCzas >= 2000)
  {
    // Zapamiętanie aktualnego czasu
    poprzedniCzas = aktualnyCzas;
    // Przejście do etapu 2
    etap = 2;
  }
  // ETAP 2
   // Ten etap trwa 4 sekundy
  if(etap == 2 && aktualnyCzas - poprzedniCzas >= 4000)
  {
    // Zapamiętanie aktualnego czasu
    poprzedniCzas = aktualnyCzas;
    // Przejście do etapu 3
    etap = 3;
  }
  // ETAP 3
  // Ten etap trwa 2 sekundy
  if (etap == 3 && aktualnyCzas - poprzedniCzas >= 2000)
  {
    // Zapamiętanie aktualnego czasu
    poprzedniCzas = aktualnyCzas;
    // Powrót do etapu 0 i rozpoczęcie cyklu od początku
    etap = 0;
  }
  
  // USTAWIENIA ŚWIATEŁ DLA POSZCZEGÓLNYCH ETAPÓW
  // ETAP 0
  // Prawa: zielona
  // Lewa: czerwona
  if(etap == 0)
  {
    digitalWrite(ledgreen1, HIGH);
    digitalWrite(ledred1, LOW);
    digitalWrite(ledgreen2, LOW);
    digitalWrite(ledred2, HIGH);
  }
  // ETAP 1
  // Obie strony: czerwone
  if(etap == 1)
  {
    digitalWrite(ledgreen1, LOW);
    digitalWrite(ledred1, HIGH);
    digitalWrite(ledgreen2, LOW);
    digitalWrite(ledred2, HIGH);
  }
  // ETAP 2
  // Prawa: czerwona
  // Lewa: zielona
  if(etap == 2)
  {
    digitalWrite(ledgreen1, LOW);
    digitalWrite(ledred1, HIGH);
    digitalWrite(ledgreen2, HIGH);
    digitalWrite(ledred2, LOW);
  }
  // ETAP 3
  // Obie strony: czerwone
  if (etap == 3)
  {
    digitalWrite(ledgreen1, LOW);
    digitalWrite(ledred1, HIGH);
    digitalWrite(ledgreen2, LOW);
    digitalWrite(ledred2, HIGH);
  }
  
}