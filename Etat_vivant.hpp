#pragma once
#include "Etat.hpp"

namespace JeuDeLaVie {

    class EtatVivant : public Etat_cellule {
    public:
        EtatVivant() = default; // Constructeur maintenant public
        ~EtatVivant() override = default;

        bool estVivante() const override;

        // Retourne un std::unique_ptr
        std::unique_ptr<Etat_cellule> determinerProchainEtat(int nbVoicins) override;
    };

}
