#include <iostream>

using namespace std;

// Pojedynczy element listy
struct kolejka
{
    int liczba;
    kolejka* next;
};

class lista
{
    kolejka* poczatek;

public:

    // Na pocz¹tku lista nie zawiera ¿adnych elementów
    lista()
    {
        poczatek = nullptr;
    }

    void dodaj(int wartosc)
    {
        kolejka* element = new kolejka;

        element->liczba = wartosc;
        element->next = nullptr;

        // Je¿eli lista jest pusta, nowy element zostaje jej pocz¹tkiem
        if (poczatek == nullptr)
        {
            poczatek = element;
        }
        else
        {
            kolejka* aktualny = poczatek;

            // Szukamy ostatniego elementu
            while (aktualny->next != nullptr)
            {
                aktualny = aktualny->next;
            }

            aktualny->next = element;
        }
    }

    // Destruktor zwalnia pamiêæ zajmowan¹ przez wszystkie elementy
    ~lista()
    {
        while (poczatek != nullptr)
        {
            kolejka* usuwany = poczatek;
            poczatek = poczatek->next;

            delete usuwany;
        }
    }
};

int main()
{
    lista mojaLista;

    mojaLista.dodaj(10);
    mojaLista.dodaj(20);
    mojaLista.dodaj(30);

    return 0;
}
