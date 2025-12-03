#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Grille.hpp"

class Jeu {
private:
    bool mode_console;
    int iterations_max;  // 0 = pas de limite
    std::string chemin;
    double pause;
    std::vector<std::string> historique;  // Pour détecter la stabilité
    
public:
    Jeu(std::string c, bool mc, int im, double p);
    void simulation();
    bool stabilite(const std::string& etat_actuel);  // Prend l'état en paramètre
};
