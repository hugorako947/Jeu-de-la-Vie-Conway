#pragma once
#include <iostream>

namespace JeuDeLaVie {
    class ReglesConway{
    public:
        ReglesConway() = default;

        bool vivante(int nbVoisins);

        bool morte(int nbVoisins);
    };
}
