#pragma once
#include <string>
#include <SFML/Graphics.hpp>    
#include <SFML/System.hpp>      
#include "Grille.hpp"

namespace JeuDeLaVie {

    class JeuGraphique {
    private:
        // --- Membres SFML ---
        sf::RenderWindow fenetre;//ce qui va permettre de creer le jeu physiquement  
        sf::Clock horloge; //ce qui va permettre de mettre une horloge pour les rafraichissement 

        int lignes;//le nombre de ligne de la grille 
        int colonnes; //le nombre de colonne de la grille 
        int taille_cellule; //la taille que l'on veut afficher pour une cellule 
        bool enPause;  // flag pour savoir si le jeu est en pause 

        // Méthodes internes (privées)
        void traiterEvenements(); //traite si l'utilisateur appuis sur une touche ou sur la souris etc 
        void dessinerGrille(const Grille& grille); // Contient la logique de dessin 

    public:
        JeuGraphique(int lignes, int colonnes, float taille_cellule_initiale = 10.0f);
        ~JeuGraphique();
        
        bool fenetreEstOuverte() const { return fenetre.isOpen(); } //méthode pour verifier que la fenetre est toujours ouverte 
        void mettreAJourAffichage(const Grille& grille); //methode pour declencher le rendu 
        void fermer() { fenetre.close(); } //pour fermer automatiquement la fenetre 
        
        // Méthodes pour gérer la pause
        bool estEnPause() const { return enPause; }
        void setPause(bool pause) { enPause = pause; }
    };
}
