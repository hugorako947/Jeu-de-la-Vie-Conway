#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

namespace JeuDeLaVie {
    class Fichiers{
    private:
        std::string chemin;
        int lignes;
        int colonnes;
    public:
        Fichiers(std::string c);

        std::vector<int> lire();
        
        int getLignes() const;
        int getColonnes() const;
    };
}
