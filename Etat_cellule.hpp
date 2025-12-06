#pragma once
#include <memory>

namespace JeuDeLaVie {
    class Etat_cellule {
    public:  
        virtual ~Etat_cellule() = default;  

        virtual bool estVivante() const = 0;
        virtual std::unique_ptr<Etat_cellule> determinerProchainEtat(int nbVoicins) = 0;
    };
}
