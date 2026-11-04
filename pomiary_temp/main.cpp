
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

// Struktura przechowujaca jeden pomiar
struct Pomiar {
    string id;             // ID stacji
    string data;           // Data pomiaru
    double temperatura;   // Temperatura
    double wiatr;         // Predkosc wiatru
};

class Pomiary {
    vector<Pomiar> baza;   // Wektor przechowujacy pomiary

public:

    // Wczytywanie pomiarow z pliku
    // Brak parametrow, dane pobierane z pliku pomiary.txt
    void wczytaj() {
        ifstream plik("pomiary.txt");
        string linia;

        if (!plik) {
            cout << "Blad otwarcia pliku!";
        }
        else {
            while (getline(plik, linia)) {
                try {
                    Pomiar p;

                    char* tekst = &linia[0];
                    char* s;

                    // Znalezienie srednika i odczyt ID
                    s = strchr(tekst, ';');

                    if (s != NULL) {
                        *s = '\0';
                        p.id = tekst;

                        // Odczyt daty
                        tekst = s + 1;
                        s = strchr(tekst, ';');

                        if (s != NULL) {
                            *s = '\0';
                            p.data = tekst;

                            // Odczyt temperatury
                            tekst = s + 1;
                            s = strchr(tekst, ';');

                            if (s != NULL) {
                                *s = '\0';
                                p.temperatura = stod(tekst);

                                // Odczyt predkosci wiatru
                                tekst = s + 1;
                                s = strchr(tekst, ';');

                                if (s != NULL) {
                                    *s = '\0';
                                    p.wiatr = stod(tekst);

                                    // Dodanie pomiaru do wektora
                                    baza.push_back(p);
                                }
                            }
                        }
                    }
                }
                catch (...) {
                    cout << "Blad odczytu!" << endl;
                }
            }

            plik.close();
        }
    }

    // 2. Znalezienie rekordu z minimalna temperatura
    // Brak parametrow, funkcja wyszukuje minimum w wektorze
    void minimum() {
        if (baza.empty()) {
            cout << "Brak pomiarow!";
        }
        else {
            Pomiar min = baza[0];

            for (int i = 0; i < baza.size(); i++) {
                if (baza[i].temperatura < min.temperatura) {
                    min = baza[i];
                }
            }

            // Wyswietlenie calego rekordu
            cout << "Stacja: " << min.id << endl;
            cout << "Data: " << min.data << endl;
            cout << "Temperatura: " << min.temperatura << endl;
            cout << "Wiatr: " << min.wiatr << endl;
        }
    }

    // 3. Wyszukiwanie pomiarow z temperatura wieksza od progu
    // Parametr prog - temperatura podana przez uzytkownika
    void szukaj(double prog) {
        bool znaleziono = false;

        for (int i = 0; i < baza.size(); i++) {
            if (baza[i].temperatura > prog) {
                cout << baza[i].id << " "
                     << baza[i].data << " "
                     << baza[i].temperatura << " "
                     << baza[i].wiatr << endl;

                znaleziono = true;
            }
        }

        if (znaleziono == false) {
            cout << "Nie znaleziono pomiarow!";
        }
    }
};

int main() {
    Pomiary p;   // Utworzenie obiektu klasy Pomiary

    p.wczytaj(); // Wczytanie danych z pliku

    cout << "\n--- MINIMALNA TEMPERATURA ---\n";
    p.minimum(); // Znalezienie najnizszej temperatury

    double prog;

    cout << "\nPodaj prog temperatury: ";
    cin >> prog;

    cout << "\n--- POMIARY POWYZEJ PROGU ---\n";
    p.szukaj(prog); // Wyszukiwanie pomiarow powyzej progu

    return 0;
}
