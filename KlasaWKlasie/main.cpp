#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

using namespace std;
class Osoba //klasa do pojedynczej osoby
{
private:
    string imie;
    string nazwisko;
    int nr;

public:
    void wczytaj_z_klawiatury() //metoda do wczytania z klawiatury
    {
        cin >> imie >> nazwisko >> nr;
    }

    void wczytaj(ifstream &plik)  //metoda do wczytania z pliku
    {
        plik >> imie >> nazwisko >> nr;
    }
    void wypisz()      //metoda do wypisywania
    {
        cout << imie << " " << nazwisko << " " << nr << endl;
    }
};

class Klasa   //klasa do klasy
{
private:
    string nazwa;
    string wychowawca;
    Osoba osoba[30];

public:
    void wczytaj_z_klawiatury(const int &ile)   //metoda do wczytania z klawiatury
    {
        cin >> nazwa;
        cin >> wychowawca;

        for(int i = 0; i < ile; i++)
        {
            osoba[i].wczytaj_z_klawiatury();
        }
    }
    void wczytaj(ifstream &plik, const int &ile)  //metoda do wczytania z pliku
    {
        plik >> nazwa;
        plik >> wychowawca;

        for(int i = 0; i < ile; i++)
        {
            osoba[i].wczytaj(plik);
        }
    }
    void wypisz(const int &ile)    //metoda do wypisania
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
    int ile = 2;    //ilosc osob w klasie
    Klasa klasa1;    //zainicjowanie klasa1
    bool zPliku;
    uint8_t wybor;
    cout<<"z pliku '1' czy z klawiatury '2'?(\n";
    cin>>wybor;
    if(wybor=='1'){
    ifstream plik("a.txt");    //otwarcie pliku a.txt
    klasa1.wczytaj(plik, ile);    //wczytanie z pliku
    plik.close();    //zamkniecie pliku
    klasa1.wypisz(ile);    //wypisanie klasy
    }
    else{
    klasa1.wczytaj_z_klawiatury(ile);    //wczytanie z klawiatury
    klasa1.wypisz(ile);   //wypisanie klasy
    }
    return 0;
}
