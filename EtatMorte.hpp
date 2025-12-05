#pragma once
#include "Etat_Cellule.hpp"

namespace JeuDeLaVie {

    class EtatMort : public Etat_cellule {
    public:
        EtatMort() = default; // Constructeur maintenant public
        ~EtatMort() override = default;

        bool estVivante() const override;

        // Retourne un std::unique_ptr
        std::unique_ptr<Etat_cellule> determinerProchainEtat(int nbVoicins) override;
    };

}
