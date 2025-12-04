#pragma once
#include <string>
#include <SFML/Graphics.hpp>    
#include <SFML/System.hpp>      
#include "Jeu.hpp"              

namespace JeuDeLaVie {

    class JeuGraphique {
    private:
        Jeu jeu_modele;

        // --- Membres SFML ---
        sf::RenderWindow fenetre;
        sf::Clock horloge;

        float temps_par_iteration;
        int taille_cellule = 10;

        int lignes;
        int colonnes;

        // Méthodes internes (privées)
        void traiterEvenements();
        void dessinerGrille();

    public:
        JeuGraphique(const std::string& chemin_fichier, float pause_sec);
        void executer();

    };

}
