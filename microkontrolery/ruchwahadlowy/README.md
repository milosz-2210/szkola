Kod steruje czterema diodami LED, które symulują światła na dwóch stronach skrzyżowania. Program wykorzystuje funkcję millis() do odmierzania czasu i przełącza się między 4 etapami:

Etap 0 – 4 s: jedna strona ma zielone, druga czerwone.

Etap 1 – 2 s: obie strony mają czerwone.

Etap 2 – 4 s: druga strona ma zielone, pierwsza czerwone.

Etap 3 – 2 s: obie strony mają czerwone.

Po etapie 3 program wraca do etapu 0 i cały cykl zaczyna się od nowa.
