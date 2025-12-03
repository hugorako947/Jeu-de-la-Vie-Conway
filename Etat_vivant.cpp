#include "EtatVivant.hpp"
#include "Etat.hpp"
#include "EtatMort.hpp" // Nécessaire pour créer l'état mort
#include <memory>

namespace JeuDeLaVie {

    bool EtatVivant::estVivante() const {
        return true;
    }

    std::unique_ptr<Etat_cellule> EtatVivant::determinerProchainEtat(int nbVoicins) {
        // Règle de Conway (1) & (3) : Sous-population (< 2) ou Surpopulation (> 3) -> MEURT
        if (nbVoicins < 2 || nbVoicins > 3) {
            // Crée et retourne le nouvel état MORT
            return std::make_unique<EtatMort>();
        }

        // Règle de Conway (2) : Survie (2 ou 3 voisines) -> SURVIT
        // Si l'état ne change pas, on crée et retourne un nouvel état VIVANT (le même type).
        return std::make_unique<EtatVivant>();
    }

}
