
#include <iostream>
#include <stdexcept>
using namespace std;

class Noeud {
public:
    int valeur;
    Noeud* suivant;

    Noeud(int v) {
        valeur = v;
        suivant = nullptr;
    }
};

class File {
private:
    Noeud* debut;
    Noeud* fin;
    int nbElements;

public:
    File() {
        debut = nullptr;
        fin = nullptr;
        nbElements = 0;
    }

    bool estVide() {
        return debut == nullptr;
    }

    bool estPleine() {
        return false;
    }

    void enfiler(int valeur) {
        Noeud* nouveau = new Noeud(valeur);

        if (estVide()) {
            debut = nouveau;
            fin = nouveau;
        }
        else {
            fin->suivant = nouveau;
            fin = nouveau;
        }

        nbElements++;
        cout << valeur << " ajoute a la file." << endl;
    }

    int defiler() {
        if (estVide()) {
            throw runtime_error("Erreur : la file est vide !");
        }

        Noeud* temp = debut;
        int valeur = temp->valeur;

        debut = debut->suivant;

        if (debut == nullptr) {
            fin = nullptr;
        }

        delete temp;
        nbElements--;

        return valeur;
    }

    void afficher() {
        if (estVide()) {
            cout << "La file est vide !" << endl;
            return;
        }

        Noeud* courant = debut;

        cout << "Debut -> ";

        while (courant != nullptr) {
            cout << courant->valeur << " -> ";
            courant = courant->suivant;
        }

        cout << "NULL" << endl;
    }

    int taille() {
        return nbElements;
    }

    ~File() {
        while (!estVide()) {
            Noeud* temp = debut;
            debut = debut->suivant;
            delete temp;
        }

        fin = nullptr;
        cout << "Memoire liberee !" << endl;
    }
};

int main() {
    File f;
    int choix, valeur;

    do {
        cout << "\n===== MENU FILE D'ATTENTE =====" << endl;
        cout << "1. Enfiler un element" << endl;
        cout << "2. Defiler un element" << endl;
        cout << "3. Afficher la file" << endl;
        cout << "4. Verifier si la file est vide" << endl;
        cout << "5. Verifier si la file est pleine" << endl;
        cout << "6. Afficher la taille" << endl;
        cout << "0. Quitter" << endl;

        cout << "Votre choix : ";
        cin >> choix;

        switch (choix) {
        case 1:
            cout << "Donner une valeur : ";
            cin >> valeur;
            f.enfiler(valeur);
            break;

        case 2:
            try {
                valeur = f.defiler();
                cout << "Element retire : " << valeur << endl;
            }
            catch (const exception& e) {
                cout << e.what() << endl;
            }
            break;

        case 3:
            f.afficher();
            break;

        case 4:
            cout << (f.estVide() ? "La file est vide." :
                     "La file n'est pas vide.") << endl;
            break;

        case 5:
            cout << (f.estPleine() ? "La file est pleine." :
                     "La file n'est pas pleine.") << endl;
            break;

        case 6:
            cout << "Taille : " << f.taille() << endl;
            break;

        case 0:
            cout << "Fin du programme." << endl;
            break;

        default:
            cout << "Choix invalide !" << endl;
        }

    } while (choix != 0);

    return 0;
}
