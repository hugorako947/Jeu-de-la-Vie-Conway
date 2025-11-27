#pragma once
#include "Etat_cellule.hpp" 
#include "Regles.hpp"

class Etat_morte : public Etat_cellule{
public:
    ~Etat_morte() override = default;
    // Implémentation de la méthode héritée (retourne toujours faux)
    bool estVivante() const override;
    // Implémentation de la méthode héritée : détermine le nouvel état basé sur les règles
    Etat_cellule* determinerProchainEtat(int nbVoisins, const ReglesConway& regles) override;
};
