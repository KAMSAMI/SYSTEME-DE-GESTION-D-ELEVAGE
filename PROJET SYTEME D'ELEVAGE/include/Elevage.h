#ifndef ELEVAGE_H
#define ELEVAGE_H

#include <vector>
#include <string>
#include "Animal.h"

using namespace std;

class Elevage {
private:
    vector<Animal> animaux;

    // M�thodes utilitaires pour la gestion des fichiers
    vector<string> lireFichier(const string& fichier) const;
    void ecrireFichier(const string& fichier, const vector<string>& lignes) const;

public:
    void ajouterAnimal(string type, string nom, string date_naissance, float poids, string sante = "Bon", bool en_reproduction = false, int nombre_jeunes = 0);
    void mettreAJourAnimal(string nom, float nouveau_poids, string nouvelle_sante, bool nouvelle_reproduction, int nouveaux_jeunes);
    void afficher() const;
    void rechercheParType(string type) const;
    void rechercheParNom(string nom) const;
    void rapport() const; // G�n�re le rapport
    void sauvegarderDansFichier(const string& fichier) const;
    void afficherFichier(const string& fichier) const;
};

#endif
