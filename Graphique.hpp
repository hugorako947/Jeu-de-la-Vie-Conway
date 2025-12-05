#include "Graphique.hpp"
#include "Grille.hpp"
#include "Cellule.hpp"
#include <iostream>
#include <thread>
#include <chrono>

namespace JeuDeLaVie {

    JeuGraphique::JeuGraphique(int lignes, int colonnes, float taille_cellule_initiale) 
        : lignes(lignes), colonnes(colonnes), taille_cellule(taille_cellule_initiale) {
        
        // Calculer la taille de la fenêtre
        int fenetre_largeur = colonnes * taille_cellule;
        int fenetre_hauteur = lignes * taille_cellule;
        
        // Limiter la taille maximale de la fenêtre
        const int MAX_SIZE = 1200;
        if (fenetre_largeur > MAX_SIZE || fenetre_hauteur > MAX_SIZE) {
            taille_cellule = MAX_SIZE / std::max(colonnes, lignes);
            fenetre_largeur = colonnes * taille_cellule;
            fenetre_hauteur = lignes * taille_cellule;
            std::cout << "Grille trop grande, ajustement automatique..." << std::endl;
            std::cout << "Nouvelle taille de cellule: " << taille_cellule << "px" << std::endl;
        }
        
        // Créer la fenêtre SFML
        fenetre.create(sf::VideoMode(fenetre_largeur, fenetre_hauteur), 
                      "Jeu de la Vie");
        fenetre.setFramerateLimit(60);
        
        std::cout << "Fenetre: " << fenetre_largeur << " x " << fenetre_hauteur << " pixels" << std::endl;
        std::cout << "Controles:" << std::endl;
        std::cout << "  ESC    : Quitter" << std::endl;
        std::cout << "  ESPACE : Pause/Reprise\n" << std::endl;
    }

    JeuGraphique::~JeuGraphique() {
        if (fenetre.isOpen()) {
            fenetre.close();
        }
    }

    void JeuGraphique::traiterEvenements() {
        sf::Event event;
        while (fenetre.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                fenetre.close();
            }
            
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        fenetre.close();
                        break;
                        
                    case sf::Keyboard::Space:
                        // Espace pour mettre en pause (à implémenter si besoin)
                        break;
                        
                    default:
                        break;
                }
            }
        }
    }

    void JeuGraphique::dessinerGrille(const Grille& grille) {
        // Effacer l'écran avec fond noir
        fenetre.clear(sf::Color(0, 0, 0)); // Noir
        
        // Dessiner les cellules vivantes
        sf::RectangleShape celluleShape(sf::Vector2f(taille_cellule - 1, taille_cellule - 1));
        celluleShape.setFillColor(sf::Color(255, 255, 255)); // Blanc
        
        for (int i = 0; i < lignes; ++i) {
            for (int j = 0; j < colonnes; ++j) {
                const Cellule& cellule = grille.get_cellule(i, j);
                if (cellule.estVivante()) {
                    celluleShape.setPosition(j * taille_cellule, i * taille_cellule);
                    fenetre.draw(celluleShape);
                }
            }
        }
        
        // Afficher à l'écran
        fenetre.display();
    }

    void JeuGraphique::mettreAJourAffichage(const Grille& grille) {
        // Traiter les événements (fermeture, touches, etc.)
        traiterEvenements();
        
        // Dessiner la grille actuelle
        dessinerGrille(grille);
        
        // Petite pause pour éviter de surcharger le CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
