    #pragma once
    #include "Etat.hpp"
    #include <memory> 
    #include <vector> 

    namespace JeuDeLaVie {
        class Grille;
        class Cellule {
        private:
            // Utilisation de unique_ptr : la Cellule est l'unique propriétaire de ses objets d'état.
            std::unique_ptr<Etat_cellule> etat_actuel;
            std::unique_ptr<Etat_cellule> prochain_etat;

        public:
            // Constructeur par défaut (Morte par défaut)
            Cellule();
            bool estVivante() const;
            void setEtatVivant();
            void setEtatMort();

            // CALCULE LE PROCHAIN ÉTAT (la Cellule délègue le calcul à l'état actuel)
            void calculerProchainEtat(int nb_voisins);

            // APPLIQUE LE PROCHAIN ÉTAT (échange l'état futur avec l'état actuel)
            void appliquerProchainEtat();
        };

    }
