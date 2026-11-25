
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cctype>

using namespace std;


// MASZYNA STANOW
enum Stan {
    OTWARTY,
    ZAMYKANIE,
    MANDAT,
    ZAMKNIETY,
    ALARM,
    PRZEJAZD_POCIAGU,
    OTWIERANIE,
    MANDAT_OTWIERANIE
};


// ZMIENNE SYSTEMOWE
Stan stan = OTWARTY;

bool przeszkoda = false;
bool alarm = false;

int liczbaMandatow = 0;


// =====================================================
// FUNKCJA: nazwaStanu()
// Zwraca nazwe aktualnego stanu maszyny stanow.
// Parametry: brak.
// Zwraca: string - nazwa aktualnego stanu.
// =====================================================

string nazwaStanu() {
    switch (stan) {
        case OTWARTY: return "OTWARTY";
        case ZAMYKANIE: return "ZAMYKANIE";
        case MANDAT: return "MANDAT";
        case ZAMKNIETY: return "ZAMKNIETY";
        case ALARM: return "ALARM";
        case PRZEJAZD_POCIAGU: return "PRZEJAZD POCIAGU";
        case OTWIERANIE: return "OTWIERANIE";
        case MANDAT_OTWIERANIE: return "MANDAT - OTWIERANIE";
    }
    return "NIEZNANY";
}


// =====================================================
// FUNKCJA: pokazStan()
// Wyswietla aktualny stan przejazdu, polozenie szlabanow,
// stan swiatel, przeszkody, alarmu i liczbe mandatow.
// Parametry: brak.
// Zwraca: void.
// =====================================================

void pokazStan() {
    cout << "\n====================================\n";
    cout << "     SYSTEM PRZEJAZDU KOLEJOWEGO\n";
    cout << "====================================\n";

    cout << "Stan: " << nazwaStanu() << endl;

    cout << "Szlabany: ";

    if (stan == OTWARTY)
        cout << "OTWARTE\n";
    else
        cout << "ZAMKNIETE / W RUCHU\n";

    cout << "Czerwone swiatla: "
         << (stan == OTWARTY ? "WYLACZONE" : "WLACZONE") << endl;

    cout << "Przeszkoda: "
         << (przeszkoda ? "WYKRYTA" : "BRAK") << endl;

    cout << "Alarm: "
         << (alarm ? "WLACZONY" : "WYLACZONY") << endl;

    cout << "Liczba mandatow: " << liczbaMandatow << endl;

    cout << "====================================\n";
}


// =====================================================
// FUNKCJA: wystawMandat()
// Rejestruje wykryte naruszenie i zwieksza licznik
// mandatow o jeden.
// Parametry: brak.
// Zwraca: void.
// =====================================================

void wystawMandat() {
    liczbaMandatow++;

    cout << "\n!!! WYKRYTO NARUSZENIE !!!\n";
    cout << "Zapisano zdarzenie do weryfikacji.\n";
    cout << "Numer zdarzenia: " << liczbaMandatow << endl;
}


// =====================================================
// FUNKCJA: wykryjPociag()
// Symuluje wykrycie nadjezdzajacego pociagu.
// Rozpoczyna zamykanie szlabanow.
// Parametry: brak.
// Zwraca: void.
// =====================================================

void wykryjPociag() {

    if (stan != OTWARTY) {
        cout << "Przejazd nie jest w stanie OTWARTYM!\n";
        return;
    }

    cout << "\nWykryto nadjezdzajacy pociag!\n";
    cout << "Wlaczanie swiatel i zamykanie szlabanow...\n";

    stan = ZAMYKANIE;
}


// =====================================================
// FUNKCJA: pojazdPodczasZamykania()
// Symuluje wykrycie pojazdu podczas zamykania szlabanow.
// Rejestruje naruszenie i przechodzi do stanu ZAMKNIETY.
// Parametry: brak.
// Zwraca: void.
// =====================================================

void pojazdPodczasZamykania() {

    if (stan != ZAMYKANIE) {
        cout << "Szlabany nie sa w trakcie zamykania.\n";
        return;
    }

    stan = MANDAT;
    wystawMandat();

    stan = ZAMKNIETY;

    cout << "Szlabany zamkniete.\n";
}


// =====================================================
// FUNKCJA: zakonczZamykanie()
// Symuluje calkowite zamkniecie szlabanow.
// Zmienia aktualny stan na ZAMKNIETY.
// Parametry: brak.
// Zwraca: void.
// =====================================================

void zakonczZamykanie() {

    if (stan != ZAMYKANIE) {
        cout << "Nie trwa zamykanie.\n";
        return;
    }

    stan = ZAMKNIETY;

    cout << "Szlabany calkowicie zamkniete.\n";
}


// =====================================================
// FUNKCJA: sprawdzPrzeszkode()
// Sprawdza, czy na przejezdzie znajduje sie przeszkoda.
// Jesli tak, uruchamia alarm. Jesli nie, pozwala
// na rozpoczecie przejazdu pociagu.
// Parametry: brak.
// Zwraca: void.
// =====================================================

void sprawdzPrzeszkode() {

    if (stan != ZAMKNIETY) {
        cout << "Przejazd nie jest zamkniety.\n";
        return;
    }

    if (przeszkoda) {
        stan = ALARM;
        alarm = true;

        cout << "\n!!! ALARM !!!\n";
        cout << "Wykryto przeszkode na przejezdzie!\n";
    }
    else {
        stan = PRZEJAZD_POCIAGU;

        cout << "Przejazd wolny.\n";
        cout << "Pociag moze przejechac.\n";
    }
}


// =====================================================
// FUNKCJA: przejazdPociagu()
// Symuluje przejazd pociagu przez przejazd kolejowy.
// Odlicza 10 sekund, a nastepnie zmienia stan
// na OTWIERANIE.
// Parametry: brak.
// Zwraca: void.
// =====================================================

void przejazdPociagu() {

    if (stan != PRZEJAZD_POCIAGU) {
        cout << "Pociag nie moze teraz przejechac.\n";
        return;
    }

    cout << "\nPociag przejezdza przez przejazd...\n";

    for (int i = 10; i > 0; i--) {
        cout << "Pozostalo sekund: " << i << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    cout << "Pociag opuscil przejazd.\n";

    stan = OTWIERANIE;
}


// =====================================================
// FUNKCJA: usunPrzeszkode()
// Symuluje usuniecie przeszkody z przejazdu.
// Jesli alarm byl wlaczony, wylacza go i przechodzi
// do stanu PRZEJAZD_POCIAGU.
// Parametry: brak.
// Zwraca: void.
// =====================================================

void usunPrzeszkode() {

    przeszkoda = false;

    cout << "Przeszkoda usunieta.\n";

    if (stan == ALARM) {
        alarm = false;
        stan = PRZEJAZD_POCIAGU;

        cout << "Alarm wylaczony.\n";
        cout << "Pociag moze przejechac.\n";
    }
}


// =====================================================
// FUNKCJA: pojazdPodczasOtwierania()
// Symuluje wykrycie pojazdu podczas podnoszenia szlabanow.
// Rejestruje naruszenie i przechodzi do stanu OTWARTY.
// Parametry: brak.
// Zwraca: void.
// =====================================================

void pojazdPodczasOtwierania() {

    if (stan != OTWIERANIE) {
        cout << "Szlabany nie sa w trakcie otwierania.\n";
        return;
    }

    stan = MANDAT_OTWIERANIE;
    wystawMandat();

    stan = OTWARTY;

    cout << "Przejazd otwarty.\n";
}


// =====================================================
// FUNKCJA: zakonczOtwieranie()
// Symuluje calkowite otwarcie szlabanow.
// Zmienia stan na OTWARTY i wylacza czerwone swiatla.
// Parametry: brak.
// Zwraca: void.
// =====================================================

void zakonczOtwieranie() {

    if (stan != OTWIERANIE) {
        cout << "Nie trwa otwieranie.\n";
        return;
    }

    stan = OTWARTY;

    cout << "Szlabany calkowicie otwarte.\n";
    cout << "Czerwone swiatla wylaczone.\n";
}


// =====================================================
// FUNKCJA GLOWNA: main()
// Odpowiada za dzialanie calego programu.
// Wyswietla menu, pobiera wybor uzytkownika
// i wywoluje odpowiednie funkcje.
// Parametry: brak.
// Zwraca: 0 po poprawnym zakonczeniu programu.
// =====================================================

int main() {

    char wybor;

    do {

        // Wyswietlenie aktualnego stanu przejazdu.
        pokazStan();

        // Menu symulujace dzialanie czujnikow.
        cout << "\n--- PANEL CZUJNIKOW ---\n";
        cout << "1 - Wykryj pociag\n";
        cout << "2 - Wykryj pojazd podczas zamykania\n";
        cout << "3 - Zakoncz zamykanie szlabanow\n";
        cout << "4 - Wykryj przeszkode na przejezdzie\n";
        cout << "5 - Sprawdz przejazd\n";
        cout << "6 - Przejazd pociagu (10 sekund)\n";
        cout << "7 - Usun przeszkode\n";
        cout << "8 - Wykryj pojazd podczas otwierania\n";
        cout << "9 - Zakoncz otwieranie szlabanow\n";

        cout << "\nQ - Wyjscie\n";

        // Pobranie wyboru uzytkownika.
        cout << "\nWybor: ";
        cin >> wybor;

        // Zamiana malej litery na duza.
        wybor = toupper(wybor);

        // Wywolanie odpowiedniej funkcji
        // na podstawie wyboru uzytkownika.
        switch (wybor) {

            case '1':
                wykryjPociag();
                break;

            case '2':
                pojazdPodczasZamykania();
                break;

            case '3':
                zakonczZamykanie();
                break;

            case '4':
                przeszkoda = true;
                cout << "Czujnik wykryl przeszkode.\n";
                break;

            case '5':
                sprawdzPrzeszkode();
                break;

            case '6':
                przejazdPociagu();
                break;

            case '7':
                usunPrzeszkode();
                break;

            case '8':
                pojazdPodczasOtwierania();
                break;

            case '9':
                zakonczOtwieranie();
                break;

            case 'Q':
                cout << "Zamykanie programu.\n";
                break;

            default:
                cout << "Nieznana komenda!\n";
        }

    } while (wybor != 'Q');

    return 0;
}
