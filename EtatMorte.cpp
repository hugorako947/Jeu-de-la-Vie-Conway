#include "EtatMort.hpp"
#include "EtatVivant.hpp" // Nécessaire pour créer l'état vivant
#include <memory>

namespace JeuDeLaVie {

    bool EtatMort::estVivante() const {
        return false;
    }

    std::unique_ptr<Etat_cellule> EtatMort::determinerProchainEtat(int nbVoicins) {
        // Règle de Conway : Une cellule morte revient à la vie si elle a EXACTEMENT 3 voisines.
        if (nbVoicins == 3) {
            // Crée et retourne le nouvel état VIVANT
            return std::make_unique<EtatVivant>();
        }
        // Si l'état ne change pas, on crée et retourne un nouvel état MORT (le même type).
        return std::make_unique<EtatMort>();
    }

}
