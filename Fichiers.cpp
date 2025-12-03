#include <iostream>
#include <stdexcept>
#include "Fichiers.hpp"
#include <string>
#include <sstream>
 
namespace JeuDeLaVie {
    Fichiers::Fichiers(std::string c) : chemin(c), lignes(0), colonnes(0) {}
    
    std::vector<int> Fichiers::lire(){
        std::ifstream fichier(chemin);
        std::vector<int> donnees_1d;
    
        if (!fichier.is_open()){
            throw std::runtime_error("ERREUR : Impossible d'ouvrir le fichier " + chemin + " !\n");
        }

        std::string ligne;

        if (std::getline(fichier, ligne)){
            std::istringstream iss(ligne);
            if (!(iss >> lignes >> colonnes)){
                throw std::runtime_error("ERREUR : Dimensions de la grille incoherentes !\n");
            }
        }else{
            throw std::runtime_error("ERREUR : Fichier vide !\n");
        }

        int total_cells = lignes * colonnes;
        int cells_read = 0;
        int etat_cellule;

        while (fichier >> etat_cellule && cells_read < total_cells){
            if (etat_cellule != 0 && etat_cellule != 1){
                throw std::runtime_error("ERREUR : Donnee de cellule invalide !\n");
            }
            donnees_1d.push_back(etat_cellule);
            cells_read++;
        }
        if (cells_read != total_cells){
            throw std::runtime_error("ERREUR : Nombre total de cellules incoherent ! Attendu : " + std::to_string(total_cells) + ", Lu : " + std::to_string(cells_read) + "\n");
        }
        fichier.close();
        return donnees_1d;
    }

    int Fichiers::getLignes() const {
        return lignes;
    }

    int Fichiers::getColonnes() const {
        return colonnes;
    }
}
