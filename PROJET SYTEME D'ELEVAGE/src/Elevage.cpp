#include "Elevage.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

vector<string> Elevage::lireFichier(const string& fichier) const {
    ifstream file(fichier);
    vector<string> lignes;
    string ligne;

    if (file.is_open()) {
        while (getline(file, ligne)) {
            lignes.push_back(ligne);
        }
        file.close();
    } else {
        cout << "Erreur lors de l'ouverture du fichier.\n";
    }
    return lignes;
}

void Elevage::ecrireFichier(const string& fichier, const vector<string>& lignes) const {
    ofstream file(fichier);
    if (file.is_open()) {
        for (const auto& ligne : lignes) {
            file << ligne << endl;
        }
        file.close();
    } else {
        cout << "Erreur lors de l'ecriture dans le fichier.\n";
    }
}

void Elevage::ajouterAnimal(string type, string nom, string date_naissance, float poids, string sante, bool en_reproduction, int nombre_jeunes) {
    Animal animal(type, nom, date_naissance, poids, sante, en_reproduction, nombre_jeunes);
    animaux.push_back(animal);

    // Ajouter directement au fichier
    ofstream file("elevage_data.txt", ios::app);
    if (file.is_open()) {
        file << "Type: " << type << ", Nom: " << nom << ", Date de Naissance: " << date_naissance
             << ", Poids: " << poids << "kg, Sante: " << sante
             << ", Reproduction: " << (en_reproduction ? "Oui" : "Non")
             << ", Nombre de Jeunes: " << nombre_jeunes << endl;
        file.close();
    } else {
        cout << "Erreur lors de l'ouverture du fichier pour l'ajout.\n";
    }
}

void Elevage::mettreAJourAnimal(string nom, float nouveau_poids, string nouvelle_sante, bool nouvelle_reproduction, int nouveaux_jeunes) {
    vector<string> lignes = lireFichier("elevage_data.txt");
    bool trouve = false;

    for (auto& ligne : lignes) {
        istringstream stream(ligne);
        string type, animal_nom, date_naissance, poids_texte, sante_texte, reproduction_texte, jeunes_texte;

        // Extraction des informations depuis la ligne
        getline(stream, type, ',');
        getline(stream, animal_nom, ',');
        getline(stream, date_naissance, ',');
        getline(stream, poids_texte, ',');
        getline(stream, sante_texte, ',');
        getline(stream, reproduction_texte, ',');
        getline(stream, jeunes_texte, ',');

        // Vérifi si l'animal correspond
        if (animal_nom.find(nom) != string::npos) {
            // Cree une nouvelle ligne mise à jour
            ostringstream nouvelle_ligne;
            nouvelle_ligne << "Type: " << type.substr(type.find(":") + 2) // Supprime "Type: " du champ
                           << ", Nom: " << nom
                           << ", Date de Naissance: " << date_naissance.substr(date_naissance.find(":") + 2) // Supprime "Date de Naissance: "
                           << ", Poids: " << nouveau_poids << "kg"
                           << ", Sante: " << nouvelle_sante
                           << ", Reproduction: " << (nouvelle_reproduction ? "Oui" : "Non")
                           << ", Nombre de Jeunes: " << nouveaux_jeunes;
            ligne = nouvelle_ligne.str();
            trouve = true;
        }
    }

    if (trouve) {
        ecrireFichier("elevage_data.txt", lignes);
        cout << "Informations de l'animal mises a jour avec succees.\n";
    } else {
        cout << "Animal non trouve.\n";
    }
}

void Elevage::afficher() const {
    for (const auto& animal : animaux) {
        animal.afficher();
    }
}

void Elevage::rechercheParType(string type) const {
    cout << "Recherche d'animaux de type : " << type << "\n";
    vector<string> lignes = lireFichier("elevage_data.txt");
    bool trouve = false;

    for (const auto& ligne : lignes) {
        if (ligne.find("Type: " + type) != string::npos) {
            cout << ligne << endl;
            trouve = true;
        }
    }

    if (!trouve) {
        cout << "Aucun animal de type " << type << " trouve.\n";
    }
}

void Elevage::rechercheParNom(string nom) const {
    cout << "Recherche d'un animal avec le nom : " << nom << "\n";
    vector<string> lignes = lireFichier("elevage_data.txt");
    bool trouve = false;

    for (const auto& ligne : lignes) {
        if (ligne.find("Nom: " + nom) != string::npos) {
            cout << ligne << endl;
            trouve = true;
            break;
        }
    }

    if (!trouve) {
        cout << "Aucun animal nomme " << nom << " trouve.\n";
    }
}

void Elevage::rapport() const {
    // Variables pour compter les types et le nombre de jeunes
    map<string, int> animaux_par_type;
    map<string, int> jeunes_par_type;

    // Lire les données du fichier
    vector<string> lignes = lireFichier("elevage_data.txt");

    for (const auto& ligne : lignes) {
        try {
            // Extraction des données à partir de la ligne
            istringstream stream(ligne);
            string type, nom, date_naissance, poids_texte, sante, reproduction, jeunes_texte;

            // Exemple de ligne : "Type: vache, Nom: Bella, Date de Naissance: 2023-01-01, Poids: 500kg, Santé: Bon, Reproduction: Oui, Nombre de Jeunes: 3"
            getline(stream, type, ',');
            getline(stream, nom, ',');
            getline(stream, date_naissance, ',');
            getline(stream, poids_texte, ',');
            getline(stream, sante, ',');
            getline(stream, reproduction, ',');
            getline(stream, jeunes_texte, ',');

            // Nettoyer et récupérer les valeurs pertinentes
            type = type.substr(type.find(":") + 2); // Supprime "Type: "
            jeunes_texte = jeunes_texte.substr(jeunes_texte.find(":") + 2); // Supprime "Nombre de Jeunes: "

            // Convertir le nombre de jeunes en entier
            int jeunes = stoi(jeunes_texte);

            // Mettre à jour les compteurs
            animaux_par_type[type]++;
            jeunes_par_type[type] += jeunes;

        } catch (const std::exception& e) {
            cout << "Erreur lors du traitement d'une ligne : " << ligne << "\n";
            cout << "Détails : " << e.what() << "\n";
            continue; // Ignorer cette ligne et passer à la suivante
        }
    }

    // Affichage du rapport
    cout << "Rapport de l'élevage :\n";
    for (const auto& [type, count] : animaux_par_type) {
        cout << "Type : " << type << ", Nombre d'animaux : " << count
             << ", Nombre total de jeunes : " << jeunes_par_type[type] << "\n";
    }
}

void Elevage::sauvegarderDansFichier(const string& fichier) const {
    vector<string> lignes;
    for (const auto& animal : animaux) {
        ostringstream ligne;
        ligne << "Type: " << animal.type << ", Nom: " << animal.nom << ", Date de Naissance: " << animal.date_naissance
              << ", Poids: " << animal.poids << "kg, Sante: " << animal.sante
              << ", Reproduction: " << (animal.en_reproduction ? "Oui" : "Non")
              << ", Nombre de Jeunes: " << animal.nombre_jeunes;
        lignes.push_back(ligne.str());
    }
    ecrireFichier(fichier, lignes);
    cout << "Donnees sauvegardees dans le fichier avec succes.\n";
}

void Elevage::afficherFichier(const string& fichier) const {
    vector<string> lignes = lireFichier(fichier);
    for (const auto& ligne : lignes) {
        cout << ligne << endl;
    }
}
