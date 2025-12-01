#pragma once
#include <iostream>
namespace JeuDeLaVie {

    class Cellule {
    private:
        bool est_vivante;
        bool prochain_etat_vivant;
    public:
        // Constructeur par défaut : la cellule est Morte (false) à la création.
        Cellule();
        // Utilisé par Grille::compterVoisinesVivantes et Cellule::afficher
        bool estVivante() const;
        void setEtatVivant();
        void setEtatMort();

        // Simplifie le calcul de l'état futur (sera appelée par Grille::mettreAJour).
        void calculerProchainEtat(int nb_voisines_vivantes);
        // Applique le nouvel état calculé (sera appelée par Grille::mettreAJour).
        void appliquerProchainEtat();
    };

} 
