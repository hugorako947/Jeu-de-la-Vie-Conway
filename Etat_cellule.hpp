#pragma once
#include <memory> // Pour std::unique_ptr

namespace JeuDeLaVie {
    class Etat_cellule {
    protected:
        // Le destructeur virtuel est essentiel
        virtual ~Etat_cellule() = default;

    public:
        virtual bool estVivante() const = 0;

        // Le retour utilise un pointeur intelligent pour transférer la propriété
        // du nouvel objet d'état à la Cellule.
        virtual std::unique_ptr<Etat_cellule> determinerProchainEtat(int nbVoicins) = 0;
    };

}
