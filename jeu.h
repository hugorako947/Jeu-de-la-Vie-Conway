#pragma once
#include <iostream>
#include "grille.h"
#include "regles.h"

class JeuDeLaVie{
private:
    Grille grille;
    ReglesConway* regles;
    bool mode_console;
    int iterations_max;
public:
    JeuDeLaVie(Grille g, ReglesConway* r, bool mc, int im);

    void simulation(std::string chemin);

    void iterations();

    bool stabilite();
};
