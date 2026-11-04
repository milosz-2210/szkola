Stacja pogodowa – Pomiary
Opis projektu

Program służy do obsługi pomiarów stacji pogodowych. Wczytuje dane z pliku tekstowego, przechowuje je w wektorze oraz umożliwia wyszukiwanie pomiarów na podstawie temperatury.

Wykorzystane technologie
C++
Biblioteka STL
vector – przechowywanie pomiarów
fstream – odczyt danych z pliku
string – przechowywanie tekstu
strchr() – wyszukiwanie separatorów w pliku
try-catch – obsługa błędów
Struktura danych

Program wykorzystuje strukturę Pomiar, która zawiera:

id – identyfikator stacji pogodowej
data – data pomiaru
temperatura – temperatura powietrza
wiatr – prędkość wiatru
Funkcjonalności programu
Wczytywanie danych z pliku – odczytywanie pomiarów z pliku pomiary.txt i zapisywanie ich do wektora.
Minimalna temperatura – wyszukiwanie pomiaru z najniższą temperaturą i wyświetlanie całego rekordu.
Wyszukiwanie pomiarów – wyświetlanie wszystkich rekordów, w których temperatura jest większa od progu podanego przez użytkownika.
Obsługa błędów – wykorzystanie mechanizmu try-catch podczas odczytu danych.
Format pliku pomiarowego

Dane w pliku pomiary.txt zapisane są w następującym formacie:

text
ID_STACJI; DATA; TEMPERATURA; WIATR;


Przykładowe dane:

text
STO1; 2026-03-01; 18.5; 12.5;
STO2; 2026-03-01; 10.1; 43;
STO3; 2026-03-01; -2.5; 15.2;
STO4; 2026-03-01; 14.2; 11.3;

Uruchomienie programu
Skompiluj program w środowisku obsługującym C++.
Umieść plik pomiary.txt w folderze z plikiem wykonywalnym programu.
Uruchom program.
Program wyświetli rekord z minimalną temperaturą.
Podaj próg temperatury, aby wyświetlić pomiary z temperaturą większą od podanej wartości.
Struktura projektu
text
pomiary_temp/
│
├── main.cpp
├── pomiary.txt
└── README.md

Autor

Projekt edukacyjny – obsługa pomiarów stacji pogodowej w języku C++.
