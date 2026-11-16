// Dołączenie bibliotek obsługujących wyświetlacz LCD oraz klawiaturę
#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>

// Utworzenie obiektu wyświetlacza LCD
Adafruit_LiquidCrystal lcd_1(0);

// Określenie liczby wierszy i kolumn klawiatury
const byte ROWS = 4;
const byte COLS = 4;

// Tablica zawierająca układ przycisków klawiatury
const char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Przypisanie pinów Arduino do wierszy i kolumn klawiatury
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

// Utworzenie obiektu klawiatury i przypisanie do niego pinów
Keypad keypad = Keypad(makeKeymap(keys),
                       rowPins, colPins, ROWS, COLS);

// Zmienne przechowujące pierwszą i drugą liczbę
String liczba1 = "";
String liczba2 = "";

// Zmienna przechowująca wybrany znak działania matematycznego
char znak = 0;

// Informacja, czy użytkownik wpisuje drugą liczbę
bool druga = false;

// Informacja, czy wynik został już wyświetlony
bool wynikPokazany = false;


// Funkcja wyświetlająca aktualne działanie na ekranie LCD
void pokazDzialanie()
{
  // Wyczyszczenie ekranu
  lcd_1.clear();

  // Wyświetlenie pierwszej liczby w pierwszym wierszu
  lcd_1.print(liczba1);

  // Sprawdzenie, czy wybrano już działanie matematyczne
  if (znak != 0)
  {
    // Przejście do drugiego wiersza wyświetlacza
    lcd_1.setCursor(0, 1);

    // Wyświetlenie odpowiedniego znaku działania
    if (znak == 'A') lcd_1.print("+");
    if (znak == 'B') lcd_1.print("-");
    if (znak == 'C') lcd_1.print("*");
    if (znak == 'D') lcd_1.print("/");

    // Wyświetlenie drugiej liczby
    lcd_1.print(liczba2);
  }
}


// Funkcja wykonywana tylko raz po uruchomieniu Arduino
void setup()
{
  // Inicjalizacja wyświetlacza LCD o wymiarach 16 kolumn i 2 wiersze
  lcd_1.begin(16, 2);

  // Włączenie podświetlenia wyświetlacza
  lcd_1.setBacklight(1);

  // Wyczyszczenie ekranu LCD
  lcd_1.clear();
}


// Główna funkcja programu wykonywana w pętli
void loop()
{
  // Odczytanie aktualnie naciśniętego przycisku klawiatury
  char klawisz = keypad.getKey();

  // Sprawdzenie, czy został naciśnięty jakikolwiek przycisk
  if (klawisz)
  {
    // RESET – przycisk * czyści kalkulator
    if (klawisz == '*')
    {
      // Wyzerowanie wszystkich zmiennych
      liczba1 = "";
      liczba2 = "";
      znak = 0;
      druga = false;
      wynikPokazany = false;

      // Wyczyszczenie wyświetlacza
      lcd_1.clear();
    }

    // WYBÓR DZIAŁANIA MATEMATYCZNEGO
    // A – dodawanie, B – odejmowanie, C – mnożenie, D – dzielenie
    else if (klawisz == 'A' || klawisz == 'B' ||
             klawisz == 'C' || klawisz == 'D')
    {
      // Sprawdzenie, czy pierwsza liczba została wpisana
      // i czy użytkownik nie wpisuje już drugiej liczby
      if (liczba1.length() > 0 && !druga)
      {
        // Zapisanie wybranego działania
        znak = klawisz;

        // Przełączenie programu na wpisywanie drugiej liczby
        druga = true;

        // Wyczyszczenie zmiennej drugiej liczby
        liczba2 = "";

        // Informacja, że nowy wynik nie został jeszcze pokazany
        wynikPokazany = false;

        // Wyświetlenie aktualnego działania na LCD
        pokazDzialanie();
      }
    }

    // OBLICZANIE WYNIKU – przycisk #
    else if (klawisz == '#')
    {
      // Sprawdzenie, czy wpisano obie liczby i wybrano działanie
      if (liczba1.length() > 0 &&
          liczba2.length() > 0 && znak != 0)
      {
        // Zamiana tekstu na liczby typu float
        float a = liczba1.toFloat();
        float b = liczba2.toFloat();

        // Zmienna przechowująca wynik obliczeń
        float wynik = 0;

        // Wykonanie dodawania
        if (znak == 'A') wynik = a + b;

        // Wykonanie odejmowania
        if (znak == 'B') wynik = a - b;

        // Wykonanie mnożenia
        if (znak == 'C') wynik = a * b;

        // Wykonanie dzielenia
        if (znak == 'D')
        {
          // Sprawdzenie, czy nie próbujemy dzielić przez zero
          if (b == 0)
          {
            // Wyczyszczenie wyświetlacza
            lcd_1.clear();

            // Wyświetlenie komunikatu o błędzie
            lcd_1.print("Blad!");
            lcd_1.setCursor(0, 1);
            lcd_1.print("Dzielenie przez 0");

            // Wyzerowanie zmiennych kalkulatora
            liczba1 = "";
            liczba2 = "";
            znak = 0;
            druga = false;
            wynikPokazany = false;

            // Zakończenie aktualnego obiegu funkcji loop()
            return;
          }

          // Jeśli dzielnik nie jest zerem, wykonanie dzielenia
          wynik = a / b;
        }

        // Zamiana wyniku na tekst z dokładnością do dwóch miejsc po przecinku
        liczba1 = String(wynik, 2);

        // Wyczyszczenie drugiej liczby
        liczba2 = "";

        // Wyzerowanie znaku działania
        znak = 0;

        // Powrót do wpisywania pierwszej liczby
        druga = false;

        // Zapisanie informacji, że wynik został wyświetlony
        wynikPokazany = true;

        // Wyczyszczenie ekranu LCD
        lcd_1.clear();

        // Wyświetlenie znaku równości
        lcd_1.print("=");

        // Przejście do drugiego wiersza
        lcd_1.setCursor(0, 1);

        // Wyświetlenie obliczonego wyniku
        lcd_1.print(liczba1);
      }
    }

    // WPISYWANIE CYFR OD 0 DO 9
    else if (klawisz >= '0' && klawisz <= '9')
    {
      // Jeśli użytkownik wpisuje pierwszą liczbę
      if (!druga)
      {
        // Jeśli poprzedni wynik został pokazany,
        // rozpoczęcie nowego działania
        if (wynikPokazany)
        {
          liczba1 = "";
          wynikPokazany = false;
        }

        // Ograniczenie pierwszej liczby do 7 cyfr
        if (liczba1.length() < 7)
          liczba1 += klawisz;
      }
      else
      {
        // Jeśli użytkownik wpisuje drugą liczbę,
        // ograniczenie jej długości do 7 cyfr
        if (liczba2.length() < 7)
          liczba2 += klawisz;
      }

      // Odświeżenie wyświetlacza i pokazanie aktualnego działania
      pokazDzialanie();
    }
  }
}