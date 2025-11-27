#pragma once
#include <iostream>

class ReglesConway {
public:
    ReglesConway() = default;

    bool vivante(int nbVoisins);

    bool morte(int nbVoisins);

    bool stop(int iteration_actuelle, bool grille_stable);
};
