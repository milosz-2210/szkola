# 🚦 Maszyna zdarzeń – Przejazd kolejowy

## 📌 Opis projektu
Projekt przedstawia symulację działania przejazdu kolejowego z wykorzystaniem maszyny stanów. Program napisany w języku C++ w środowisku Code::Blocks.

## ⚙️ Funkcjonalności
- Wykrywanie nadjeżdżającego pociągu.
- Zamykanie i otwieranie szlabanów.
- Sterowanie światłami ostrzegawczymi.
- Wykrywanie przeszkód i uruchamianie alarmu.
- Wykrywanie nieprawidłowego wjazdu pojazdów.
- Rejestrowanie mandatów.
- Symulacja przejazdu pociągu (10 sekund).

## 🔄 Stany maszyny
- `OTWARTY`
- `ZAMYKANIE`
- `MANDAT`
- `ZAMKNIETY`
- `ALARM`
- `PRZEJAZD_POCIAGU`
- `OTWIERANIE`
- `MANDAT_OTWIERANIE`

## 🛠️ Technologie
- C++
- Code::Blocks
- Maszyna stanów (State Machine)
