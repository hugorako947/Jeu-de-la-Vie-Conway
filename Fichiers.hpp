#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

namespace JeuDeLaVie {
    class Fichiers {
    private:
        std::string chemin;
        int lignes;
        int colonnes;
    public:
        Fichiers(std::string c);

        std::vector<int> lire();
        // Méthode pour créer le dossier et écrire l'état de la grille
        void ecrire(const std::string etat, int iteration) const;

        int getLignes() const;
        int getColonnes() const;
    };
}
