#include <iostream>
using namespace std;

class Drzewo {

private:

    // Element przechowuje liczbê oraz wskaŸniki
    // na lewe i prawe dziecko
    struct Element {
        int liczba;
        Element *lewy;
        Element *prawy;
    };

    // WskaŸnik na pierwszy element drzewa, czyli korzeñ
    Element *korzen;


    // Funkcja tworzy nowy element drzewa
    Element* nowyElement(int liczba) {

        // Tworzymy element w pamiêci
        Element *nowy = new Element;

        // Ustawiamy jego wartoœæ
        (*nowy).liczba = liczba;

        // Nowy element na pocz¹tku nie ma dzieci
        (*nowy).lewy = nullptr;
        (*nowy).prawy = nullptr;

        return nowy;
    }


    // Rekurencyjna funkcja dodaj¹ca element do drzewa
    void dodaj(Element *&korzen, int liczba) {

        // Je¿eli znaleŸliœmy puste miejsce,
        // tworzymy w nim nowy element
        if (korzen == nullptr) {
            korzen = nowyElement(liczba);
            return;
        }

        // Je¿eli liczba jest mniejsza od obecnej,
        // przechodzimy do lewego poddrzewa
        if (liczba < (*korzen).liczba) {
            dodaj((*korzen).lewy, liczba);
        }

        // Je¿eli liczba jest wiêksza lub równa,
        // przechodzimy do prawego poddrzewa
        else {
            dodaj((*korzen).prawy, liczba);
        }
    }


    // Rekurencyjne wypisywanie elementów drzewa
    void wypisz(Element *korzen) {

        // Jeœli nie ma elementu, koñczymy rekurencjê
        if (korzen == nullptr) {
            return;
        }

        // Kolejnoœæ: lewe poddrzewo, korzeñ, prawe poddrzewo
        // Dziêki temu liczby zostan¹ wypisane rosn¹co
        wypisz((*korzen).lewy);
        cout << (*korzen).liczba << " ";
        wypisz((*korzen).prawy);
    }


    // Rekurencyjne usuwanie wszystkich elementów
    void usun(Element *korzen) {

        if (korzen == nullptr) {
            return;
        }

        // Najpierw usuwamy dzieci
        usun((*korzen).lewy);
        usun((*korzen).prawy);

        // Na koñcu usuwamy obecny element
        delete korzen;
    }


public:

    // Konstruktor
    // Na pocz¹tku tworzymy puste drzewo
    Drzewo() {
        korzen = nullptr;
    }


    // Publiczna funkcja dodawania liczby
    // Wywo³uje funkcjê rekurencyjn¹
    void dodaj(int liczba) {
        dodaj(korzen, liczba);
    }


    // Publiczna funkcja wypisywania drzewa
    void wypisz() {
        wypisz(korzen);
    }


    // Destruktor
    // Po zakoñczeniu programu usuwa ca³e drzewo z pamiêci
    ~Drzewo() {
        usun(korzen);
    }
};


int main() {

    // Tworzymy obiekt klasy Drzewo
    Drzewo drzewo;

    // Dodajemy kolejne liczby do drzewa
    drzewo.dodaj(4);
    drzewo.dodaj(8);
    drzewo.dodaj(6);
    drzewo.dodaj(9);
    drzewo.dodaj(5);
    drzewo.dodaj(2);
    drzewo.dodaj(7);

    cout << "Drzewo: ";

    // Wypisujemy elementy w kolejnoœci rosn¹cej
    drzewo.wypisz();

    return 0;
}
