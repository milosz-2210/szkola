
Drzewo BST w C++ Prosty program w języku C++, który tworzy i wyświetla binarne drzewo wyszukiwania (BST).

Jak działa program? Program:

tworzy strukturę pojedynczego elementu drzewa, dodaje liczby do drzewa zgodnie z zasadami BST, przechodzi przez drzewo metodą inorder, wyświetla elementy w kolejności rosnącej. Zasada dodawania Dla każdej dodawanej liczby:

jeśli jest mniejsza od wartości w korzeniu, trafia do lewego poddrzewa, jeśli jest większa lub równa, trafia do prawego poddrzewa. Do dodawania elementów wykorzystywana jest funkcja rekurencyjna dodaj().
