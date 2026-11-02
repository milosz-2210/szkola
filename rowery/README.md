Wypożyczalnia rowerów 
Opis projektu
Program konsolowy napisany w języku C++, służący do obsługi wypożyczalni rowerów. Umożliwia zarządzanie listą rowerów, ich wypożyczanie oraz zwracanie z automatycznym obliczaniem kosztów.

Funkcjonalności
Dodawanie roweru
Podanie ID roweru.
Podanie opisu i rodzaju roweru.
Ustalenie ceny za godzinę.
Automatyczne ustawienie statusu na dostępny.
Wypożyczanie roweru
Wyszukiwanie roweru po ID.
Sprawdzanie dostępności.
Zmiana statusu na wypożyczony.
Obsługa błędów, np. próby wypożyczenia zajętego roweru.
Zwracanie roweru
Wyszukiwanie roweru po ID.
Podanie liczby godzin wypożyczenia.
Automatyczne obliczanie kosztu.
Zmiana statusu roweru na dostępny.
Wyświetlanie rowerów
Wyświetlanie wszystkich rowerów w formie tabeli.
Prezentacja ID, opisu, rodzaju, ceny i statusu.
Wyjście z programu
Możliwość zakończenia działania aplikacji poprzez menu tekstowe.
Wykorzystane technologie
Język programowania C++.
Biblioteka iostream – obsługa wejścia i wyjścia.
Biblioteka vector – przechowywanie listy rowerów.
Biblioteka string – obsługa tekstu.
Biblioteka iomanip – formatowanie wyświetlanych danych.
Obsługa błędów
W programie zastosowano mechanizm try-catch oraz throw, który obsługuje między innymi:

Próby wypożyczenia już wypożyczonego roweru.
Podanie nieprawidłowego ID.
Podanie liczby godzin równej 0 lub mniejszej od 0.
Próby zwrócenia roweru, który nie jest wypożyczony.
Obliczanie kosztów
Koszt wypożyczenia obliczany jest według wzoru:

Koszt = liczba godzin × cena za godzinę

Uruchomienie programu
Sklonuj repozytorium.
Otwórz projekt w środowisku obsługującym C++.
Skompiluj plik źródłowy.
Uruchom program i korzystaj z menu tekstowego.
Cel projektu
Celem projektu jest praktyczne wykorzystanie podstaw języka C++, programowania obiektowego, wektorów, funkcji oraz obsługi wyjątków.
