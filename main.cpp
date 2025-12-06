#include <iostream>
#include "Jeu.hpp"
#include "Grille.hpp"
#include "Cellule.hpp"
#include "Etat_Cellule.hpp"
#include "EtatVivant.hpp"
#include "EtatMort.hpp"
#include "Regles.hpp"
#include "Fichier.hpp"
#include "Tests.hpp"

int main(){
    char choix1;

    std::cout << "\n------------------JEU DE LA VIE------------------\n" << std::endl;

    std::cout << "Voulez-vous lancer la simulation ou les tests unitaires ? (s/t): "; std::cin >> choix1;

    if (choix1 == 's'){
        std::string chemin_input;
        std::string chemin_output = "output/";
        char choix2;
        bool mode_console;
        int iterations_max = 1000;
        double pause = 0;

        std::cout << "\nChemin de la grille initiale: "; std::cin >> chemin_input;
        JeuDeLaVie::Fichiers fichier(chemin_input, chemin_output);
        fichier.lire();

        std::cout << "Mode console ou graphique ? (c/g): "; std::cin >> choix2;
        if (choix2 == 'c'){
            mode_console = true;
        }
        else if (choix2 == 'g'){
            mode_console = false;
        }
        else{
            std::cout << "\nERREUR: Mode invalide !\n" << std::endl;
            return 0;
        }

        std::cout << "Vitesse de lecture (seconde(s) par iterations): "; std::cin >> pause;
        if (std::cin.fail()){
            std::cout << "\nERREUR: Valeur invalide !" << std::endl;
            return 0;
        }

        Jeu jeu(chemin_input, mode_console, iterations_max, pause, chemin_output);
        jeu.simulation();

    }
    else if (choix1 == 't'){

        Jeu jeu("", true, 0, 0, "");
        jeu.tests_unitaires();

    }
    else{
        std::cout << "\nERREUR: Reponse invalide !\n" << std::endl;
        return 0;
    }
    return 0;
}
