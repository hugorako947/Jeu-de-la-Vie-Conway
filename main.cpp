#include <iostream>
#include "jeu.h"
#include "fichiers.h"
#include "regles.h"
#include "grille.h"
coucou;
int main(){
    std::string chemin;
    std::cout << "----------Jeu de la vie----------" << std::endl;
    std::cout << "Chemin de la grille initiale : "; std::cin >> chemin;

    Fichiers fichier(chemin);
    
    int** grille = fichier.lire();
    
    int lignes = fichier.getLignes();
    int colonnes = fichier.getColonnes();
    
    std::cout << "Lignes : " << lignes << std::endl;
    std::cout << "Colonnes : " << colonnes << std::endl;
    
    for (int i = 0; i < lignes; i++){
        for (int j = 0; j < colonnes; j++){
            std::cout << grille[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
