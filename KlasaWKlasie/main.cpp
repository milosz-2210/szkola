#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

using namespace std;
//klasa do pojedynczej osoby
class Osoba
{
private:
    string imie;
    string nazwisko;
    int nr;

public:
    //metoda do wczytania z klawiatury
    void wczytaj_z_klawiatury()
    {
        cin >> imie >> nazwisko >> nr;
    }
    //metoda do wczytania z pliku
    void wczytaj(ifstream &plik)
    {
        plik >> imie >> nazwisko >> nr;
    }
    //metoda do wypisywania
    void wypisz()
    {
        cout << imie << " " << nazwisko << " " << nr << endl;
    }
};

//klasa do klasy
class Klasa
{
private:
    string nazwa;
    string wychowawca;
    Osoba osoba[30];

public:
    //metoda do wczytania z klawiatury
    void wczytaj_z_klawiatury(const int &ile)
    {
        cin >> nazwa;
        cin >> wychowawca;

        for(int i = 0; i < ile; i++)
        {
            osoba[i].wczytaj_z_klawiatury();
        }
    }
    //metoda do wczytania z pliku
    void wczytaj(ifstream &plik, const int &ile)
    {
        plik >> nazwa;
        plik >> wychowawca;

        for(int i = 0; i < ile; i++)
        {
            osoba[i].wczytaj(plik);
        }
    }
    //metoda do wypisania
    void wypisz(const int &ile)
    {
        cout << "Klasa: " << nazwa << endl;
        cout << "Wychowawca: " << wychowawca << endl;

        for(int i = 0; i < ile; i++)
        {
            osoba[i].wypisz();
        }
    }
};


int main()
{
    //ilosc osob w klasie
    int ile = 2;
    //zainicjowanie klasa1
    Klasa klasa1;
    bool zPliku;
    uint8_t wybor;
    cout<<"z pliku czy z klawiatury?(z pliku '1', z klawiatury '2')\n";
    cin>>wybor;
    if(wybor=='1'){
    //otwarcie pliku a.txt
    ifstream plik("a.txt");
    //wczytanie z pliku
    klasa1.wczytaj(plik, ile);
    //zamkniecie pliku
    plik.close();
    //wypisanie klasy
    klasa1.wypisz(ile);
    }
    else{
    //wczytanie z klawiatury
    klasa1.wczytaj_z_klawiatury(ile);
    //wypisanie klasy
    klasa1.wypisz(ile);
    }
    return 0;
}
