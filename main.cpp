#include <iostream>
#include "Jeu.hpp"
#include "Grille.hpp"
#include "Cellule.hpp"
#include "Etat_cellule.hpp"
#include "Etat_vivant.hpp"
#include "Etat_morte.hpp"
#include "Regles.hpp"
#include "Fichiers.hpp"

namespace JeuDeLaVie {

int main(){
    std::string chemin;
    char choix1;
    bool mode_console;
    char choix2;
    int iterations_max = 0;

    std::cout << "----------Jeu de la vie----------" << std::endl;
    std::cout << "Chemin de la grille initiale: "; std::cin >> chemin;
    std::cout << "Mode console ou graphique ? (c/g): "; std::cin >> choix1;

    if (choix1 == 'c'){
        mode_console = true;
    }
    else if (choix1 == 'g'){
        mode_console = false;
    }
    else{
        throw std::runtime_error("Erreur : mode invalide");
    }

    std::cout << "Voulez-vous un nombre d'iterations predefinis ? (y/n): "; std::cin >> choix2;

    if (choix2 == 'y'){
        std::cout << "Nombre d'iterations: "; std::cin >> iterations_max;
    }
    else{
        if (choix2 != 'n'){
            throw std::runtime_error("Erreur : reponse invalide");
        }
    }

    std::cout << "Chargement du jeu reussi..." << std::endl;

    JeuDeLaVie jeu(chemin, mode_console, iterations_max);
    jeu.simulation();

    return 0;
}
}
