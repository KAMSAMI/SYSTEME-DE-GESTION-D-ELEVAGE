#include "Animal.h"
#include <iostream>

using namespace std;

Animal::Animal(string type, string nom, string date_naissance, float poids, string sante, bool en_reproduction, int nombre_jeunes)
    : type(type), nom(nom), date_naissance(date_naissance), poids(poids), sante(sante), en_reproduction(en_reproduction), nombre_jeunes(nombre_jeunes) {}

void Animal::afficher() const {
    cout << "Type: " << type << ", Nom: " << nom << ", Date de Naissance: " << date_naissance
         << ", Poids: " << poids << "kg, Sante: " << sante
         << ", Reproduction: " << (en_reproduction ? "Oui" : "Non")
         << ", Nombre de Jeunes: " << nombre_jeunes << endl;
}
