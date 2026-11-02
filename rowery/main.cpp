#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Klasa przechowująca informacje o rowerze
class Rower {
public:
    int id;                 // Unikalny numer roweru
    string opis;            // Opis roweru
    string rodzaj;          // Rodzaj roweru
    double cena;            // Cena za jedną godzinę
    bool wypozyczony;       // Status: true = wypożyczony, false = dostępny

    // Konstruktor - ustawia początkowe wartości roweru
    // Parametry:
    // id - numer roweru
    // opis - opis roweru
    // rodzaj - rodzaj roweru
    // cena - cena za godzinę
    Rower(int id, string opis, string rodzaj, double cena) {
        this->id = id;
        this->opis = opis;
        this->rodzaj = rodzaj;
        this->cena = cena;
        this->wypozyczony = false; // Nowy rower jest dostępny
    }
}

// Lista przechowująca wszystkie rowery
vector<Rower> rowery;


// Funkcja wyszukująca rower po jego ID
// Parametr:
// id - numer szukanego roweru
// Zwraca:
// indeks roweru w wektorze lub -1, jeśli go nie znaleziono
int znajdzRower(int id) {
    for (int i = 0; i < rowery.size(); i++) {
        if (rowery[i].id == id) {
            return i;
        }
    }

    return -1;
}


// Funkcja dodająca nowy rower do wypożyczalni
// Parametry: brak
// Zwraca: nic (void)
void dodajRower() {
    int id;
    string opis, rodzaj;
    double cena;

    cout << "Podaj ID roweru: ";
    cin >> id;

    // Sprawdzenie, czy ID już istnieje
    if (znajdzRower(id) != -1) {
        cout << "Rower o takim ID juz istnieje!\n";
        return;
    }

    cin.ignore();

    cout << "Podaj opis roweru: ";
    getline(cin, opis);

    cout << "Podaj rodzaj roweru: ";
    getline(cin, rodzaj);

    cout << "Podaj cene za godzine: ";
    cin >> cena;

    // Sprawdzenie, czy cena nie jest ujemna
    if (cena < 0) {
        cout << "Cena nie moze byc ujemna!\n";
        return;
    }

    // Dodanie nowego roweru do wektora
    rowery.push_back(Rower(id, opis, rodzaj, cena));

    cout << "Dodano rower!\n";
}


// Funkcja wypożyczająca rower
// Parametry: brak
// Zwraca: nic (void)
// Wykorzystuje try-catch do obsługi błędów
void wypozyczRower() {
    int id;

    cout << "Podaj ID roweru: ";
    cin >> id;

    try {
        // Wyszukanie roweru na podstawie ID
        int indeks = znajdzRower(id);

        // Jeśli indeks wynosi -1, rower nie istnieje
        if (indeks == -1) {
            throw string("Nie znaleziono roweru!");
        }

        // Sprawdzenie, czy rower jest już wypożyczony
        if (rowery[indeks].wypozyczony == true) {
            throw string("Blad! Rower jest juz wypozyczony.");
        }

        // Zmiana statusu na wypożyczony
        rowery[indeks].wypozyczony = true;

        cout << "Rower zostal wypozyczony!\n";
    }
    catch (string e) {
        // Wyświetlenie komunikatu o błędzie
        cout << "BLAD: " << e << endl;
    }
}


// Funkcja zwracająca rower i obliczająca koszt wypożyczenia
// Parametry: brak
// Zwraca: nic (void)
// Oblicza koszt na podstawie liczby godzin i ceny za godzinę
void zwrocRower() {
    int id;
    double godziny;

    cout << "Podaj ID roweru: ";
    cin >> id;

    try {
        // Wyszukanie roweru
        int indeks = znajdzRower(id);

        if (indeks == -1) {
            throw string("Nie znaleziono roweru!");
        }

        // Sprawdzenie, czy rower został wcześniej wypożyczony
        if (rowery[indeks].wypozyczony == false) {
            throw string("Ten rower nie jest wypozyczony!");
        }

        cout << "Podaj liczbe godzin wypozyczenia: ";
        cin >> godziny;

        // Liczba godzin musi być większa od zera
        if (godziny <= 0) {
            throw string("Liczba godzin musi byc wieksza od 0!");
        }

        // Obliczenie całkowitego kosztu wypożyczenia
        double koszt = godziny * rowery[indeks].cena;

        // Ustawienie wyświetlania dwóch miejsc po przecinku
        cout << fixed << setprecision(2);

        cout << "\n--- RACHUNEK ---\n";
        cout << "ID roweru: " << rowery[indeks].id << endl;
        cout << "Rodzaj: " << rowery[indeks].rodzaj << endl;
        cout << "Cena za godzine: " << rowery[indeks].cena << " zl\n";
        cout << "Liczba godzin: " << godziny << endl;
        cout << "Do zaplaty: " << koszt << " zl\n";

        // Po poprawnym rozliczeniu rower staje się dostępny
        rowery[indeks].wypozyczony = false;

        cout << "Rower zostal zwrocony!\n";
    }
    catch (string e) {
        // Obsługa błędów i wyświetlenie ich treści
        cout << "BLAD: " << e << endl;
    }
}


// Funkcja wyświetlająca wszystkie rowery w formie tabeli
// Parametry: brak
// Zwraca: nic (void)
void wypiszRowery() {

    // Sprawdzenie, czy lista rowerów jest pusta
    if (rowery.empty()) {
        cout << "Brak rowerow w wypozyczalni.\n";
        return;
    }

    // Nagłówki tabeli
    cout << "\n";
    cout << left
         << setw(8) << "ID"
         << setw(25) << "Opis"
         << setw(18) << "Rodzaj"
         << setw(12) << "Cena"
         << "Status\n";

    cout << "---------------------------------------------------------------\n";

    // Przejście przez wszystkie rowery w wektorze
    for (const auto& r : rowery) {
        cout << left
             << setw(8) << r.id
             << setw(25) << r.opis
             << setw(18) << r.rodzaj
             << setw(12) << r.cena
             << (r.wypozyczony ? "Wypozyczony" : "Dostepny")
             << endl;
    }
}


// Główna funkcja programu
// Parametry: brak
// Zwraca: 0, jeśli program zakończył się poprawnie
int main() {
    int wybor;

    do {
        // Menu główne programu
        cout << "\n===== WYPOZYCZALNIA ROWEROW =====\n";
        cout << "1. Dodaj rower\n";
        cout << "2. Wypozycz rower\n";
        cout << "3. Zwroc rower\n";
        cout << "4. Wypisz rowery\n";
        cout << "5. Wyjscie\n";
        cout << "Wybierz opcje: ";

        cin >> wybor;

        // Wybór operacji na podstawie numeru podanego przez użytkownika
        switch (wybor) {
            case 1:
                dodajRower();
                break;

            case 2:
                wypozyczRower();
                break;

            case 3:
                zwrocRower();
                break;

            case 4:
                wypiszRowery();
                break;

            case 5:
                cout << "Koniec programu.\n";
                break;

            default:
                cout << "Nieprawidlowa opcja!\n";
        }

    } while (wybor != 5); // Menu działa do momentu wybrania opcji 5

    return 0;
}
