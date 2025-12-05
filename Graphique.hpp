#pragma once
#include <string>
#include <SFML/Graphics.hpp>    
#include <SFML/System.hpp>      
#include "Grille.hpp"

namespace JeuDeLaVie {

    class JeuGraphique {
    private:
        // --- Membres SFML ---
        sf::RenderWindow fenetre;
        sf::Clock horloge;

        int lignes;
        int colonnes;
        int taille_cellule;
        bool enPause;  // Ajout du champ pour la pause

        // Méthodes internes (privées)
        void traiterEvenements();
        void dessinerGrille(const Grille& grille);

    public:
        JeuGraphique(int lignes, int colonnes, float taille_cellule_initiale = 10.0f);
        ~JeuGraphique();
        
        bool fenetreEstOuverte() const { return fenetre.isOpen(); }
        void mettreAJourAffichage(const Grille& grille);
        void fermer() { fenetre.close(); }
        
        // Méthodes pour gérer la pause
        bool estEnPause() const { return enPause; }
        void setPause(bool pause) { enPause = pause; }
    };
}
