#pragma once
#include <iostream>
#include "Grille.hpp"

namespace JeuDeLaVie {

class JeuDeLaVie{
private:
    bool mode_console;
    int iterations_max;
    std::string chemin;
public:
    JeuDeLaVie(std::string c, bool mc, int im);

    void simulation();

    bool stabilite();
};
}
