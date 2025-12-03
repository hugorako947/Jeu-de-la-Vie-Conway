#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

namespace JeuDeLaVie {
    class Fichiers{
    private:
        std::string chemin_input;
        std::string chemin_output;
        int lignes;
        int colonnes;
    public:
        Fichiers(std::string ci, std::string co);

        std::vector<int> lire();

        void ecrire(const std::string& etat, int iteration) const;
        
        int getLignes() const;
        int getColonnes() const;
    };
}
