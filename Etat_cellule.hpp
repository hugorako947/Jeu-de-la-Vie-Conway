#pragma once
#include <memory>

namespace JeuDeLaVie {
    class Etat_cellule {
    public:  // CHANGER DE protected À public
        virtual ~Etat_cellule() = default;  // Doit être public pour unique_ptr

        virtual bool estVivante() const = 0;
        virtual std::unique_ptr<Etat_cellule> determinerProchainEtat(int nbVoicins) = 0;
    };
}
