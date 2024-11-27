#include <iostream>
#include "Elevage.h"
#include <limits>

using namespace std;

// Fonction pour afficher un message de bienvenue
void afficherMessageBienvenue() {
    cout << "Bienvenue dans le systeme de gestion de l'elevage d'animaux !\n";
}

// Fonction pour afficher le menu principal
void afficherMenu() {
    cout << "\n======Menu======\n";
    cout << "1. Ajouter un animal\n";
    cout << "2. Mettre a jour les informations d'un animal\n";
    cout << "3. Rechercher un animal par type ou nom\n";
    cout << "4. Afficher un rapport sur le nombre d'animaux\n";
    //cout << "5. Sauvegarder les donnees dans un fichier\n";
    cout << "5. Afficher les donnees depuis un fichier\n";
    cout << "6. Quitter\n";
    cout << "Choisissez une option : ";
}

// Fonction pour executer les choix de l'utilisateur
void executerChoix(Elevage& elevage) {
    int choix;
    string type, nom, date_naissance, sante;
    float poids;
    bool en_reproduction;
    int nombre_jeunes;

    while (true) {
        afficherMenu();
        cin >> choix;

        // Verifier que l'entree utilisateur est valide
        if (cin.fail()) {
            cin.clear(); // Efface l'etat d'erreur
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore l'entr�e incorrecte
            cout << "Entree invalide. Veuillez entrer un numero correspondant a une option.\n";
            continue;
        }

        switch (choix) {
            case 1:
                // Ajouter un nouvel animal
                cout << "Entrez le type de l'animal : ";
                cin >> type;
                cout << "Entrez le nom de l'animal : ";
                cin >> nom;
                cout << "Entrez la date de naissance (YYYY-MM-DD) : ";
                cin >> date_naissance;
                cout << "Entrez le poids en kg : ";
                cin >> poids;
                cout << "Entrez l'etat de sante (Bon/Moyenne/Mauvais) : ";
                cin >> sante;
                cout << "Est-il en reproduction (1 pour oui, 0 pour non) : ";
                cin >> en_reproduction;
                cout << "Entrez le nombre de jeunes : ";
                cin >> nombre_jeunes;

                if (cin.fail() || poids <= 0 || nombre_jeunes < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Donn�es invalides. Veuillez reessayer.\n";
                } else {
                    elevage.ajouterAnimal(type, nom, date_naissance, poids, sante, en_reproduction, nombre_jeunes);
                }
                break;

            case 2:
                // Mettre a jour les informations d'un animal
                cout << "Entrez le nom de l'animal a mettre a jour : ";
                cin >> nom;
                cout << "Entrez le nouveau poids en kg : ";
                cin >> poids;
                cout << "Entrez le nouvel etat de sante : ";
                cin >> sante;
                cout << "Est-il en reproduction (1 pour oui, 0 pour non) : ";
                cin >> en_reproduction;
                cout << "Entrez le nouveau nombre de jeunes : ";
                cin >> nombre_jeunes;

                if (cin.fail() || poids <= 0 || nombre_jeunes < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Donn�es invalides. Veuillez reessayer.\n";
                } else {
                    elevage.mettreAJourAnimal(nom, poids, sante, en_reproduction, nombre_jeunes);
                }
                break;

            case 3: {
                // Rechercher un animal par type ou par nom
                cout << "Rechercher par type ou nom (1 pour type, 2 pour nom) : ";
                int rechercheChoix;
                cin >> rechercheChoix;

                if (rechercheChoix == 1) {
                    cout << "Entrez le type d'animal a rechercher : ";
                    cin >> type;
                    elevage.rechercheParType(type);
                } else if (rechercheChoix == 2) {
                    cout << "Entrez le nom de l'animal a rechercher : ";
                    cin >> nom;
                    elevage.rechercheParNom(nom);
                } else {
                    cout << "Option invalide pour la recherche. Veuillez reessayer.\n";
                }
                break;
            }

            case 4:
                // Afficher un rapport sur le nombre d'animaux
                elevage.rapport();
                break;

            /*case 5:
                // Sauvegarder les donnees dans un fichier
                elevage.sauvegarderDansFichier("elevage_data.txt");
                break;*/

            case 5:
                // Afficher les donn�es depuis un fichier
                elevage.afficherFichier("elevage_data.txt");
                break;

            case 6:
                // Quitter le programme
                cout << "Au revoir !\n";
                return;

            default:
                // Gestion des choix non valides
                cout << "Option invalide. Veuillez entrer un numero entre 1 et 6.\n";
        }
    }
}

// Point d'entr�e principal du programme
int main() {
    Elevage elevage;

    // Afficher un message de bienvenue
    afficherMessageBienvenue();

    // Lancer le menu et permettre a l'utilisateur d'interagir
    executerChoix(elevage);

    return 0;
}
