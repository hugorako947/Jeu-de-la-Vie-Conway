#include <iostream>
#include "Regles.hpp"
#include <stdexcept>

namespace JeuDeLaVie{
    bool ReglesConway::vivante(int nbVoisins){
        return (nbVoisins == 2 || nbVoisins == 3);
    }

    bool ReglesConway::morte(int nbVoisins){
        return (nbVoisins == 3);
    }
}
