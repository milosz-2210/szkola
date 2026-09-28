#include <iostream>
#include <fstream>

using namespace std;


// Struktura pojedynczego elementu listy
// Przechowuje liczbe oraz wskaznik na nastepny element
struct Element
{
    int liczba;
    Element *nastepny;
};


class SortowanieLiczb
{
    Element *poczatek;  // wskaznik na pierwszy element listy
    int ilosc;          // liczba elementow znajdujacych sie na liscie

public:

    // Konstruktor - na poczatku lista jest pusta
    SortowanieLiczb()
    {
        poczatek = NULL;
        ilosc = 0;
    }


    // Destruktor usuwa wszystkie elementy utworzone w pamieci
    ~SortowanieLiczb()
    {
        Element *pomocniczy;

        while (poczatek != NULL)
        {
            // Zapamietujemy pierwszy element
            pomocniczy = poczatek;

            // Przesuwamy poczatek na kolejny element
            poczatek = poczatek->nastepny;

            // Usuwamy poprzedni element
            delete pomocniczy;
        }
    }


    // Wyswietlanie wszystkich liczb znajdujacych sie na liscie
    void pokaz()
    {
        // Wskaznik pomocniczy zaczyna od pierwszego elementu
        Element *wsk = poczatek;

        while (wsk != NULL)
        {
            cout << wsk->liczba << " ";

            // Przechodzimy do kolejnego elementu
            wsk = wsk->nastepny;
        }

        cout << endl;
    }


    // WCZYTYWANIE DANYCH Z PLIKU
    // Funkcja pobiera liczby z pliku a.txt i dodaje je
    // kolejno na koniec listy.
    void odczytajDane()
    {
        // Otwieramy plik do odczytu
        ifstream plik("a.txt");

        // Sprawdzamy, czy plik zostal poprawnie otwarty
        if (!plik.good())
        {
            cout << "Nie udalo sie otworzyc pliku!" << endl;
            return;
        }

        int wartosc;

        // Wczytujemy liczby dopoki znajduja sie w pliku
        while (plik >> wartosc)
        {
            // Tworzymy nowy element listy
            Element *nowyElement = new Element;

            nowyElement->liczba = wartosc;
            nowyElement->nastepny = NULL;


            // Jezeli lista jest pusta,
            // nowy element zostaje jej poczatkiem
            if (poczatek == NULL)
            {
                poczatek = nowyElement;
            }
            else
            {
                // Szukamy ostatniego elementu listy
                Element *koniec = poczatek;

                while (koniec->nastepny != NULL)
                {
                    koniec = koniec->nastepny;
                }

                // Ostatni element wskazuje na nowy
                koniec->nastepny = nowyElement;
            }

            // Zwiekszamy liczbe elementow
            ilosc++;
        }

        plik.close();
    }


    // SORTOWANIE BABELKOWE
    // Sortowanie odbywa sie rosnaco.
    // Porownujemy dwa sasiadujace elementy i w razie potrzeby
    // zamieniamy ich kolejnosc na liscie.
    void sortuj()
    {
        // Dla pustej listy lub jednego elementu
        // sortowanie nie jest potrzebne
        if (poczatek == NULL || poczatek->nastepny == NULL)
        {
            return;
        }

        // Informuje, czy podczas przejscia wykonano zamiane
        bool zmieniono;


        // Petla powtarza sortowanie do momentu,
        // gdy nie zostanie wykonana zadna zamiana
        do
        {
            zmieniono = false;

            // Element znajdujacy sie przed aktualnym
            Element *poprzedni = NULL;

            // Element, ktory aktualnie sprawdzamy
            Element *aktualny = poczatek;


            // Sprawdzamy element aktualny i nastepny
            while (aktualny->nastepny != NULL)
            {
                Element *kolejny = aktualny->nastepny;


                // Jezeli liczby sa w zlej kolejnosci,
                // zmieniamy miejscami elementy listy
                if (aktualny->liczba > kolejny->liczba)
                {
                    // Przepinamy wskazniki elementow
                    aktualny->nastepny = kolejny->nastepny;
                    kolejny->nastepny = aktualny;


                    // Jezeli zamiana dotyczyla pierwszych
                    // dwoch elementow, zmieniamy poczatek listy
                    if (poprzedni == NULL)
                    {
                        poczatek = kolejny;
                    }
                    else
                    {
                        // W przeciwnym przypadku poprzedni
                        // element wskazuje teraz na kolejny
                        poprzedni->nastepny = kolejny;
                    }


                    // Zostala wykonana zamiana
                    zmieniono = true;

                    // Przesuwamy poprzedni element
                    poprzedni = kolejny;
                }
                else
                {
                    // Jezeli nie trzeba zamieniac elementow,
                    // przesuwamy wskazniki dalej
                    poprzedni = aktualny;
                    aktualny = aktualny->nastepny;
                }
            }

        // Jezeli byla zamiana, wykonujemy kolejne przejscie
        } while (zmieniono);
    }


    // ZAPISYWANIE DANYCH DO PLIKU
    // Funkcja zapisuje wszystkie liczby z listy
    // do pliku b.txt.
    void zapiszDane()
    {
        // Otwieramy plik do zapisu
        ofstream plik("b.txt");

        // Sprawdzamy, czy plik zostal otwarty
        if (!plik.good())
        {
            cout << "Nie udalo sie otworzyc pliku!" << endl;
            return;
        }

        // Zaczynamy od pierwszego elementu listy
        Element *wsk = poczatek;


        // Przechodzimy przez cala liste
        while (wsk != NULL)
        {
            // Zapisujemy aktualna liczbe
            plik << wsk->liczba << " ";

            // Przechodzimy do kolejnego elementu
            wsk = wsk->nastepny;
        }

        plik.close();
    }


    // MENU PROGRAMU
    // Funkcja pozwala uzytkownikowi wybrac operacje,
    // ktora ma zostac wykonana.
    void uruchomMenu()
    {
        int opcja;

        // Menu wyswietla sie do momentu wybrania 0
        do
        {
            cout << endl;
            cout << "1 - wczytaj dane" << endl;
            cout << "2 - sortuj liczby" << endl;
            cout << "3 - pokaz dane" << endl;
            cout << "4 - zapisz dane" << endl;
            cout << "0 - zakoncz program" << endl;

            // Pobieramy wybor uzytkownika
            cin >> opcja;


            // Wykonujemy odpowiednia funkcje
            switch (opcja)
            {
                case 1:
                    // Wczytanie danych z pliku
                    odczytajDane();
                    break;

                case 2:
                    // Posortowanie danych
                    sortuj();
                    break;

                case 3:
                    // Wyswietlenie danych
                    pokaz();
                    break;

                case 4:
                    // Zapisanie danych do pliku
                    zapiszDane();
                    break;

                case 0:
                    // Zakonczenie programu
                    cout << "Koniec programu." << endl;
                    break;

                default:
                    // Obsluga blednego wyboru
                    cout << "Nieprawidlowy wybor!" << endl;
            }

        } while (opcja != 0);
    }
};


int main()
{
    // Tworzymy obiekt klasy SortowanieLiczb
    SortowanieLiczb program;

    // Uruchamiamy glowne menu programu
    program.uruchomMenu();

    return 0;
}
