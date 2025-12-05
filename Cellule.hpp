#pragma once
#include "Etat_Cellule.hpp"
#include <memory> 

namespace JeuDeLaVie {
    class Cellule {
    private:
        std::unique_ptr<Etat_cellule> etat_actuel;
        std::unique_ptr<Etat_cellule> prochain_etat;

    public:
        // Constructeur par défaut
        Cellule();
        
        // Constructeur par déplacement
        Cellule(Cellule&& autre) noexcept;
        
        // Opérateur d'affectation par déplacement
        Cellule& operator=(Cellule&& autre) noexcept;
        
        // SUPPRIMER les constructeurs de copie
        Cellule(const Cellule&) = delete;
        Cellule& operator=(const Cellule&) = delete;

        bool estVivante() const;
        void setEtatVivant();
        void setEtatMort();
        void calculerProchainEtat(int nb_voisins);
        void appliquerProchainEtat();
    };
}
