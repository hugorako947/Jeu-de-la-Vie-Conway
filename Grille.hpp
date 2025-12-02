#pragma once
#include "Cellule.hpp"
#include <vector>
#include <string>

namespace JeuDeLaVie {

    class Grille {
    private:
        int lignes;
        int colonnes;
        std::vector<Cellule> cellules; // tableau dynamique qui va stocker l'état de chaque cellule
    public:
        Grille(int l, int c);

        // Getters
        int get_l() const;
        int get_c() const;

        // Initialisation
        void initialiser(const std::vector<Cellule>& g);

        // Accesseurs de Cellule
        Cellule& get_cellule(int l, int c);
        const Cellule& get_cellule(int l, int c) const;

        // Logique du jeu
        int compterVoisinesVivantes(int l, int c) const;
        void mettreAJour();

        // Affichage
        std::string afficher() const;
    };

} // Fin du namespace JeuDeLaVie
