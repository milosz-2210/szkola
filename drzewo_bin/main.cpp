#include <iostream>
using namespace std;

struct drzewo {
    int liczba;
    drzewo *lewy;
    drzewo *prawy;
};

drzewo* nowyElement(int liczba) {
    drzewo *nowy = new drzewo;

    nowy->liczba = liczba;
    nowy->lewy = nullptr;
    nowy->prawy = nullptr;

    return nowy;
}

drzewo* dodaj(drzewo *korzen, int liczba) {

    if (korzen == nullptr) {
        return nowyElement(liczba);
    }

    if (liczba < korzen->liczba) {
        korzen->lewy = dodaj(korzen->lewy, liczba);
    }
    else {
        korzen->prawy = dodaj(korzen->prawy, liczba);
    }

    return korzen;
}

void inorder(drzewo *korzen) {

    if (korzen == nullptr) {
        return;
    }

    inorder(korzen->lewy);
    cout << korzen->liczba << " ";
    inorder(korzen->prawy);
}

int main() {


    drzewo *korzen = nullptr;

    korzen = dodaj(korzen, 4);
    korzen = dodaj(korzen, 8);
    korzen = dodaj(korzen, 6);
    korzen = dodaj(korzen, 9);
    korzen = dodaj(korzen, 5);
    korzen = dodaj(korzen, 2);
    korzen = dodaj(korzen, 7);

    cout << "Drzewo: ";

    inorder(korzen);

    return 0;
}
