
#include <iostream>
#include <string>
using namespace std;

class Noeud {
public:
    int cle;
    string valeur;
    Noeud* suivant;

    Noeud(int c, string v) {
        cle = c;
        valeur = v;
        suivant = nullptr;
    }
};

class TableHachage {
private:
    Noeud** table;
    int tailleTable;

    int hachage(int cle) {
        return cle % tailleTable;
    }

public:
    TableHachage(int taille) {
        tailleTable = taille;
        table = new Noeud*[tailleTable];

        for (int i = 0; i < tailleTable; i++) {
            table[i] = nullptr;
        }
    }

    void inserer(int cle, string valeur) {
        int indice = hachage(cle);

        Noeud* courant = table[indice];

        while (courant != nullptr) {
            if (courant->cle == cle) {
                courant->valeur = valeur;
                return;
            }
            courant = courant->suivant;
        }

        Noeud* nouveau = new Noeud(cle, valeur);
        nouveau->suivant = table[indice];
        table[indice] = nouveau;
    }

    string rechercher(int cle) {
        int indice = hachage(cle);

        Noeud* courant = table[indice];

        while (courant != nullptr) {
            if (courant->cle == cle) {
                return courant->valeur;
            }

            courant = courant->suivant;
        }

        return "Cle introuvable";
    }

    void supprimer(int cle) {
        int indice = hachage(cle);

        Noeud* courant = table[indice];
        Noeud* precedent = nullptr;

        while (courant != nullptr) {
            if (courant->cle == cle) {

                if (precedent == nullptr) {
                    table[indice] = courant->suivant;
                }
                else {
                    precedent->suivant = courant->suivant;
                }

                delete courant;
                cout << "Element supprime !" << endl;
                return;
            }

            precedent = courant;
            courant = courant->suivant;
        }

        cout << "Cle introuvable !" << endl;
    }

    void afficher() {
        for (int i = 0; i < tailleTable; i++) {
            cout << "Case " << i << " : ";

            Noeud* courant = table[i];

            while (courant != nullptr) {
                cout << "[" << courant->cle
                     << " : " << courant->valeur << "] -> ";

                courant = courant->suivant;
            }

            cout << "NULL" << endl;
        }
    }

    ~TableHachage() {
        for (int i = 0; i < tailleTable; i++) {
            Noeud* courant = table[i];

            while (courant != nullptr) {
                Noeud* temp = courant;
                courant = courant->suivant;
                delete temp;
            }
        }

        delete[] table;
    }
};

int main() {
    TableHachage t(5);

    t.inserer(10, "Ali");
    t.inserer(15, "Sara");
    t.inserer(20, "Oumaima");
    t.inserer(7, "Karim");
    t.inserer(3, "Amine");

    cout << "Contenu de la table :" << endl;
    t.afficher();

    cout << "\nRecherche de la cle 15 : ";
    cout << t.rechercher(15) << endl;

    cout << "\nSuppression de la cle 15 :" << endl;
    t.supprimer(15);

    cout << "\nTable apres suppression :" << endl;
    t.afficher();

    return 0;
}
