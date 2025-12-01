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
        throw std::runtime_error("Erreur : impossible d'ouvrir le fichier " + chemin);
    }

    std::string ligne;

    if (std::getline(fichier, ligne)){
        std::istringstream iss(ligne);
        if (!(iss >> lignes >> colonnes)){
            throw std::runtime_error("Erreur : format de dimensions invalide (première ligne)");
        }
    }else{
        throw std::runtime_error("Erreur : fichier vide");
    }

    int total_cells = lignes * colonnes;
    int cells_read = 0;
    int etat_cellule;

    while (fichier >> etat_cellule && cells_read < total_cells){
        if (etat_cellule != 0 && etat_cellule != 1){
            throw std::runtime_error("Erreur : donnée de cellule invalide (doit être 0 ou 1).");
        }
        donnees_1d.push_back(etat_cellule);
        cells_read++;
    }
    if (cells_read != total_cells){
        throw std::runtime_error("Erreur : nombre total de cellules incohérent. Attendu : " + 
        std::to_string(total_cells) + ", Lu : " + std::to_string(cells_read));
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
