#include <iostream>
#include "Jeu.hpp"
#include "Grille.hpp"
#include "Cellule.hpp"
#include "Etat.hpp"
#include "EtatVivant.hpp"
#include "EtatMort.hpp"
#include "Regles.hpp"
#include "Fichier.hpp"

int main(){
    char choix3;

    std::cout << "\n------------------JEU DE LA VIE------------------\n" << std::endl;

    std::cout << "Voulez-vous lancer la simulation ou les tests unitaires ? (s/t): "; std::cin >> choix3;

    if (choix3 == 's'){
        std::string chemin_input;
        std::string chemin_output = "output/";
        char choix1;
        bool mode_console;
        char choix2;
        int iterations_max = 200;
        double pause = 0;

        std::cout << "\nChemin de la grille initiale: "; std::cin >> chemin_input;
        JeuDeLaVie::Fichiers fichier(chemin_input, chemin_output);
        fichier.lire();

        std::cout << "Mode console ou graphique ? (c/g): "; std::cin >> choix1;
        if (choix1 == 'c'){
            mode_console = true;
        }
        else if (choix1 == 'g'){
            mode_console = false;
        }
        else{
            std::cout << "\nERREUR : Mode invalide !\n" << std::endl;
            return 0;
        }

        Jeu jeu(chemin_input, mode_console, iterations_max, pause, chemin_output);
        jeu.simulation();

    }
    else if (choix3 == 't'){

        Jeu jeu("", true, 0, 0, "");
        jeu.tests_unitaires();

    }
    else{
        std::cout << "\nERREUR : Reponse invalide !\n" << std::endl;
        return 0;
    }
    return 0;
}
