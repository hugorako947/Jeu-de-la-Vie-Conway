#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Fichiers{
private:
    std::string chemin;
    int lignes;
    int colonnes;
public:
    Fichiers(std::string c);

    int** lire();
    
    int getLignes() const;
    int getColonnes() const;
};
