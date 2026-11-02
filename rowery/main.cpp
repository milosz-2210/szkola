#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Rower {
public:
    int id;
    string opis;
    string rodzaj;
    double cena;
    bool wypozyczony;

    Rower(int id, string opis, string rodzaj, double cena) {
        this->id = id;
        this->opis = opis;
        this->rodzaj = rodzaj;
        this->cena = cena;
        this->wypozyczony = false;
    }
};

vector<Rower> rowery;


int znajdzRower(int id) {
    for (int i = 0; i < rowery.size(); i++) {
        if (rowery[i].id == id) {
            return i;
        }
    }
    return -1;
}

void dodajRower() {
    int id;
    string opis, rodzaj;
    double cena;

    cout << "Podaj ID roweru: ";
    cin >> id;

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

    if (cena < 0) {
        cout << "Cena nie moze byc ujemna!\n";
        return;
    }

    rowery.push_back(Rower(id, opis, rodzaj, cena));

    cout << "Dodano rower!\n";
}

void wypozyczRower() {
    int id;

    cout << "Podaj ID roweru: ";
    cin >> id;

    try {
        int indeks = znajdzRower(id);

        if (indeks == -1) {
            throw string("Nie znaleziono roweru!");
        }

        if (rowery[indeks].wypozyczony == true) {
            throw string("Blad! Rower jest juz wypozyczony.");
        }

        rowery[indeks].wypozyczony = true;

        cout << "Rower zostal wypozyczony!\n";
    }
    catch (string e) {
        cout << "BLAD: " << e << endl;
    }
}

void zwrocRower() {
    int id;
    double godziny;

    cout << "Podaj ID roweru: ";
    cin >> id;

    try {
        int indeks = znajdzRower(id);

        if (indeks == -1) {
            throw string("Nie znaleziono roweru!");
        }

        if (rowery[indeks].wypozyczony == false) {
            throw string("Ten rower nie jest wypozyczony!");
        }

        cout << "Podaj liczbe godzin wypozyczenia: ";
        cin >> godziny;

        if (godziny <= 0) {
            throw string("Liczba godzin musi byc wieksza od 0!");
        }
        double koszt = godziny * rowery[indeks].cena;

        cout << fixed << setprecision(2);
        cout << "\n--- RACHUNEK ---\n";
        cout << "ID roweru: " << rowery[indeks].id << endl;
        cout << "Rodzaj: " << rowery[indeks].rodzaj << endl;
        cout << "Cena za godzine: " << rowery[indeks].cena << " zl\n";
        cout << "Liczba godzin: " << godziny << endl;
        cout << "Do zaplaty: " << koszt << " zl\n";

        rowery[indeks].wypozyczony = false;

        cout << "Rower zostal zwrocony!\n";
    }
    catch (string e) {
        cout << "BLAD: " << e << endl;
    }
}

void wypiszRowery() {
    if (rowery.empty()) {
        cout << "Brak rowerow w wypozyczalni.\n";
        return;
    }

    cout << "\n";
    cout << left
         << setw(8) << "ID"
         << setw(25) << "Opis"
         << setw(18) << "Rodzaj"
         << setw(12) << "Cena"
         << "Status\n";

    cout << "----------------------------------------------------------------------\n";

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

int main() {
    int wybor;

    do {
        cout << "\n===== WYPOZYCZALNIA ROWEROW =====\n";
        cout << "1. Dodaj rower\n";
        cout << "2. Wypozycz rower\n";
        cout << "3. Zwroc rower\n";
        cout << "4. Wypisz rowery\n";
        cout << "5. Wyjscie\n";
        cout << "Wybierz opcje: ";

        cin >> wybor;

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

    } while (wybor != 5);

    return 0;
}
