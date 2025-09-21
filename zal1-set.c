#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Pomocnicza funkcja minimum z dwóch wartości.
#define MIN(a,b) ((a) < (b) ? (a) : (b))
// Liczba wszystkich kart w talii SET.
#define TALIA 81
// Liczba kart w secie.
#define SET 3
// Domyślna liczba wykładanych na stół kart w jednym zagraniu.
#define STOL 12

// Funkcja aktualizuje obecny stan stołu po każdym zagraniu.
void aktualizacjaStolu (int stol[], int dane[], int ileNaStol) {
    // Wypełnianie tablicy stol zerami.
    bool zero = false;
    for (int i = 0; i < TALIA && !zero; i++) {
        if (stol[i] != 0) {
            stol[i] = 0;
        }
        else {
            zero = true;
        }
    }
    // Uzupełnienie tablicy stol odpowiednią liczbą kart z tablicy dane.
    // Liczba obrotów pętli, z każdą -1 na tablicy, dodajemy jeden obrót pętli
    int liczKart = ileNaStol;
    int indeks = 0; // Indeks do przechodzenia się po tablicy stol.
    for (int i = 0; i < liczKart; i++) {
        if (dane[i] == -1) {
            liczKart++;
        }
        else {
            stol[indeks] = dane[i];
            indeks++;
        }
    }
}

// Funkcja po każdym secie zamienia karty tego seta z tablicy dane na -1 tak,
// aby mieć pewność, że nie uwzględnimy ich po raz drugi w talii kart.
void aktualizacjaDanych(int dane[], int N, int karta1, int karta2, int karta3) {
    // Zamiana odpowiednich kart na -1.
    for (int i = 0; i < N; i++) {
        if (dane[i] == karta1 || dane[i] == karta2 || dane[i] == karta3) {
            dane[i] = -1;
        }
    }
}

// Funkcja wypisuje obecny stan stołu.
void wypiszStol (int stol[], int ileNaStol) {
    printf("=");
    for (int i = 0; i < ileNaStol; i++) {
        printf(" %d", stol[i]);
    }
    printf("\n");
}

// Funkcja wypisuje seta.
void wypiszSeta (int karta1, int karta2, int karta3) {
    printf("- %d %d %d\n", karta1, karta2, karta3);
}

// Funkcja dostaje w argumentach wartości trzech kart i zwraca true, gdy podane
// karty tworzą seta i false, gdy tak nie jest.
bool czySet (int karta1, int karta2, int karta3) {
    // Wartości atrybutów odpowiednio karty pierwszej, drugiej i trzeciej.
    int a1, a2, a3; 
    // Wartość logiczna, czy wartości danego atrybutu w trzech kartach
    // są wszystkie takie same lub wszystkie różne.
    bool zgadzaSie = true;
    // Atrybuty otrzymujemy poprzez resztę z dzielenia przez 10.
    for (int i = 0; i < 4 && zgadzaSie; i++) {
        a1 = karta1 % 10;
        a2 = karta2 % 10;
        a3 = karta3 % 10;
        // Warunek na seta.
        if (!((a1 == a2 && a2 == a3) || (a1 + a2 + a3 == 6 && a1 != a2))) {
            zgadzaSie = false;
        }
        karta1 /= 10;
        karta2 /= 10;
        karta3 /= 10;
        }
    return zgadzaSie;
}

// Funkcja wczytuje input na tablicę.
void wczytajDane (int dane[]) {
    int karta;
    int i = 0;
    while (scanf("%d", &karta) == 1) {
        dane[i] = karta;
        i++;
    }
}

// Pomocnicza funkcja, która wypełnia tablicę zerami.
void zerujTablice(int A[], int N) {
    for (int i = 0; i < N; i++) {
        A[i] = 0;
    }
}

int main () {
    // Tablica na dane.
    int dane[TALIA];
    zerujTablice(dane, TALIA);
    // Tablica na aktualny stan stołu.
    int stol[TALIA];
    zerujTablice(stol, TALIA);
    // Wypełniamy tablicę dane danymi.
    wczytajDane(dane);
    // Ile kart otrzymaliśmy w inpucie.
    int ileKart = 0;
   // Zliczenie wartości zmiennej ileKart.
    for (int i = 0; i < TALIA; i++) {
        if (dane[i] != 0) {
            ileKart++;
        }
    }
    // Informacja czy w kartach, ktore pozostały, jest set.
    bool jestSet = true;
    // Informacja, czy w obecnym przeszukiwaniu znaleźliśmy seta.
    bool set;
    // Ile kart chcemy wyłożyć (niezależnie od tego, ile zostało w talii).
    int ileWykladamy = STOL;
    // Ile kart z naszych danych jeszcze nie wystąpiło w żadnym secie.
    int ileZostalo = ileKart;   
    // Ile rzeczywiście wykładamy kart, biorąc pod uwagę ile chcemy
    // i ile możemy, czyli ile zostało w talii (minimum z tych wartości).
    int ileNaStol = MIN(ileWykladamy, ileZostalo);
    // Pierwsza aktualizacja stanu stołu.
    aktualizacjaStolu(stol, dane, ileNaStol);
    // Pierwsze wypisanie stołu.
    wypiszStol(stol, ileNaStol);
    // Szukamy setów wśród danych kart dopóki możliwe jest znalezienie seta.
    while (jestSet && ileZostalo > 0) {
        // Szukanie seta wśród kart na stole.
        set = false;
        for (int i = 0; i < ileNaStol - 2 && !set; i++) {
            for (int j = i + 1; j < ileNaStol - 1 && !set; j++) {
                for (int k = j + 1; k < ileNaStol && !set; k++) {
                    // Jeśli znaleźliśmy seta to wypisujemy go, usuwamy z danych
                    // poprzez zamianę na -1, aktualizujemy liczbę pozostałych 
                    // w talii kart i ustawiamy ileWykladamy na minimum z 
                    // 12 i liczby kart, które pozostały w talii.
                    if (czySet(stol[i], stol[j], stol[k])) {
                        set = true;
                        wypiszSeta(stol[i], stol[j], stol[k]);
                        aktualizacjaDanych(
                            dane, 
                            ileKart, 
                            stol[i], 
                            stol[j], 
                            stol[k]
                        );
                        ileZostalo -= SET;
                        ileWykladamy = (ileWykladamy - 3 > STOL) ? ileWykladamy - 3 : STOL;
                    }
                }
            }
        }
        if (!set) {
            // Jeśli set nie wystąpił, a wyciągnęliśmy już wszystkie karty (na
            // stół) to kończymy pętlę nadając wartość false zmiennej jestSet.
            if (ileWykladamy >= ileZostalo) {
                jestSet = false;
            } 
            // Jeśli set nie wystąpił, ale jeszcze nie wyciągnęliśmy wszystkich
            // kart to w następnym ruchu na stół wyciągamy 3 dodatkowe karty
            // i wypisujemy odpowiednią linijkę.
            else {
                ileWykladamy += SET;
                printf("+\n");
            }
        }
        if (jestSet) {
            ileNaStol = MIN(ileWykladamy, ileZostalo);
            // Po każdym szukaniu seta aktualizujemy stan stołu.
            aktualizacjaStolu(stol, dane, ileNaStol);
            // I wypisujemy stan stołu.
            wypiszStol(stol, ileNaStol);
        }
    }
    return 0;
}