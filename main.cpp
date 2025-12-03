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
    std::string chemin_input;
    std::string chemin_output;
    char choix1;
    bool mode_console;
    char choix2;
    int iterations_max = 0;
    double pause;

    std::cout << "" << std::endl;
    std::cout << "------------------JEU DE LA VIE------------------" << std::endl;
    std::cout << "" << std::endl;

    std::cout << "Chemin de la grille initiale: "; std::cin >> chemin_input;
    JeuDeLaVie::Fichiers fichier(chemin_input, chemin_output);
    fichier.lire();

    std::cout << "Mode console ou graphique ? (c/g): "; std::cin >> choix1;
    if (choix1 == 'c'){
        mode_console = true;
        std::cout << "Chemin des grilles de chaque iterations: "; std::cin >> chemin_output;
    }
    else if (choix1 == 'g'){
        mode_console = false;
    }
    else{
        std::cout << "\nERREUR : Mode invalide !\n" << std::endl;
        return 0;
    }

    std::cout << "Voulez-vous un nombre d'iterations predefinis ? (y/n): "; std::cin >> choix2;
    if (choix2 == 'y'){
        std::cout << "Nombre d'iterations: "; std::cin >> iterations_max;
        if (std::cin.fail()){
            std::cout << "\nERREUR : Valeur invalide !\n" << std::endl;
            return 0;
        }
    }
    else{
        if (choix2 != 'n'){
            std::cout << "\nERREUR : Reponse invalide !\n" << std::endl;
            return 0;
        }
    }

    std::cout << "Temps de pause entre chaques iterations (secondes): "; std::cin >> pause;
    if (std::cin.fail()){
        std::cout << "\nERREUR : Valeur invalide !\n" << std::endl;
        return 0;
    }

    Jeu jeu(chemin_input, mode_console, iterations_max, pause, chemin_output);
    jeu.simulation();

    return 0;
}
