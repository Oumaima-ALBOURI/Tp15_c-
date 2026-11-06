
#include <iostream>
using namespace std;

// =====================================
// 1. Classe Noeud
// =====================================
class Noeud {
public:
    int valeur;
    Noeud* suivant;

    Noeud(int v) {
        valeur = v;
        suivant = nullptr;
    }
};

// =====================================
// 2. Classe ListeChainee
// =====================================
class ListeChainee {
private:
    Noeud* tete;
    int nombreElements;

public:

    // Constructeur
    ListeChainee() {
        tete = nullptr;
        nombreElements = 0;
    }

    // Ajouter au debut
    void ajouterDebut(int valeur) {
        Noeud* nouveau = new Noeud(valeur);

        nouveau->suivant = tete;
        tete = nouveau;

        nombreElements++;
    }

    // Ajouter a la fin
    void ajouterFin(int valeur) {
        Noeud* nouveau = new Noeud(valeur);

        if (tete == nullptr) {
            tete = nouveau;
        }
        else {
            Noeud* courant = tete;

            while (courant->suivant != nullptr) {
                courant = courant->suivant;
            }

            courant->suivant = nouveau;
        }

        nombreElements++;
    }

    // Supprimer une valeur
    void supprimer(int valeur) {

        if (tete == nullptr) {
            cout << "La liste est vide !" << endl;
            return;
        }

        // Si la valeur est dans le premier noeud
        if (tete->valeur == valeur) {
            Noeud* temp = tete;
            tete = tete->suivant;

            delete temp;
            nombreElements--;
            return;
        }

        // Recherche du noeud a supprimer
        Noeud* courant = tete;

        while (courant->suivant != nullptr &&
               courant->suivant->valeur != valeur) {

            courant = courant->suivant;
        }

        // Si la valeur existe
        if (courant->suivant != nullptr) {
            Noeud* temp = courant->suivant;

            courant->suivant = temp->suivant;

            delete temp;
            nombreElements--;
        }
        else {
            cout << "Valeur introuvable !" << endl;
        }
    }

    // Afficher la liste
    void afficher() {
        Noeud* courant = tete;

        while (courant != nullptr) {
            cout << courant->valeur << " -> ";
            courant = courant->suivant;
        }

        cout << "NULL" << endl;
    }

    // Retourner le nombre d'elements
    int taille() {
        return nombreElements;
    }

    // =====================================
    // 3. Iterateur personnalise
    // =====================================
    class Iterateur {
    private:
        Noeud* courant;

    public:
        Iterateur(Noeud* noeud) {
            courant = noeud;
        }

        // Acceder a la valeur
        int& operator*() {
            return courant->valeur;
        }

        // Passer au noeud suivant
        Iterateur& operator++() {
            courant = courant->suivant;
            return *this;
        }

        // Comparer deux iterateurs
        bool operator!=(const Iterateur& autre) const {
            return courant != autre.courant;
        }
    };

    // Debut de la liste
    Iterateur begin() {
        return Iterateur(tete);
    }

    // Fin de la liste
    Iterateur end() {
        return Iterateur(nullptr);
    }

    // =====================================
    // 4. Destructeur
    // =====================================
    ~ListeChainee() {
        Noeud* courant = tete;

        while (courant != nullptr) {
            Noeud* temp = courant;
            courant = courant->suivant;

            delete temp;
        }

        tete = nullptr;
        nombreElements = 0;

        cout << "Memoire liberee !" << endl;
    }

    // Eviter une copie superficielle de la liste
    ListeChainee(const ListeChainee&) = delete;
    ListeChainee& operator=(const ListeChainee&) = delete;
};

// =====================================
// 5. Programme principal
// =====================================
int main() {

    ListeChainee liste;

    // Ajouter des elements
    liste.ajouterDebut(20);
    liste.ajouterDebut(10);
    liste.ajouterFin(30);
    liste.ajouterFin(40);

    cout << "Liste initiale : ";
    liste.afficher();

    // Afficher la taille
    cout << "Taille : " << liste.taille() << endl;

    // Supprimer un element
    liste.supprimer(20);

    cout << "\nApres suppression de 20 : ";
    liste.afficher();

    cout << "Nouvelle taille : "
         << liste.taille() << endl;

    // Parcourir avec l'iterateur
    cout << "\nParcours avec iterateur : ";

    for (ListeChainee::Iterateur it = liste.begin();
         it != liste.end(); ++it) {

        cout << *it << " ";
    }

    cout << endl;

    // Parcours avec range-based for
    cout << "\nParcours avec for-each : ";

    for (int valeur : liste) {
        cout << valeur << " ";
    }

    cout << endl;

    return 0;
}
