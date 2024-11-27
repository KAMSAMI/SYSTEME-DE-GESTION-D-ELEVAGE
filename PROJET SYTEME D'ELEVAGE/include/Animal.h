#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
using namespace std;

class Animal {
public:
    string type;
    string nom;
    string date_naissance;
    float poids;  // Poids en kg
    string sante;
    bool en_reproduction;
    int nombre_jeunes;

    Animal(string type, string nom, string date_naissance, float poids, string sante = "Bon", bool en_reproduction = false, int nombre_jeunes = 0);
    void afficher() const;
};

#endif
