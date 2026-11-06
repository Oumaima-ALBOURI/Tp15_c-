
#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
using namespace std;

template <typename T>
class Pile {
private:
    T* elements;
    int capacite;
    int sommetIndex;

public:
    Pile(int taille = 10) {
        capacite = taille;
        elements = new T[capacite];
        sommetIndex = -1;
    }

    bool estVide() const {
        return sommetIndex == -1;
    }

    void empiler(T element) {
        if (sommetIndex == capacite - 1) {
            int nouvelleCapacite = capacite * 2;
            T* nouveau = new T[nouvelleCapacite];

            for (int i = 0; i <= sommetIndex; i++) {
                nouveau[i] = elements[i];
            }

            delete[] elements;
            elements = nouveau;
            capacite = nouvelleCapacite;
        }

        elements[++sommetIndex] = element;
    }

    T depiler() {
        if (estVide()) {
            throw runtime_error("Erreur : la pile est vide !");
        }

        return elements[sommetIndex--];
    }

    T sommet() const {
        if (estVide()) {
            throw runtime_error("Erreur : la pile est vide !");
        }

        return elements[sommetIndex];
    }

    void inverser() {
        reverse(elements, elements + sommetIndex + 1);
    }

    void afficher() const {
        if (estVide()) {
            cout << "La pile est vide !" << endl;
            return;
        }

        for (int i = sommetIndex; i >= 0; i--) {
            cout << elements[i] << endl;
        }
    }

    ~Pile() {
        delete[] elements;
    }
};

int main() {

    try {

        Pile<int> p1;

        p1.empiler(10);
        p1.empiler(20);
        p1.empiler(30);

        cout << "Pile des entiers :" << endl;
        p1.afficher();

        cout << "Sommet : " << p1.sommet() << endl;

        cout << "Element depile : " << p1.depiler() << endl;

        cout << "\nApres inversion :" << endl;
        p1.inverser();
        p1.afficher();

        Pile<string> p2;

        p2.empiler("Ali");
        p2.empiler("Sara");
        p2.empiler("Oumaima");

        cout << "\nPile des chaines :" << endl;
        p2.afficher();

        cout << "Sommet : " << p2.sommet() << endl;

        Pile<double> p3;

        p3.empiler(10.5);
        p3.empiler(20.75);
        p3.empiler(30.25);

        cout << "\nPile des reels :" << endl;
        p3.afficher();

        cout << "Element depile : " << p3.depiler() << endl;

    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
