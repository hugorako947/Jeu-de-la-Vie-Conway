#include <iostream>
#include <fstream>
#include <sstream>
#include "Fichiers.hpp"

Fichiers::Fichiers(std::string c) : chemin(c), lignes(0), colonnes(0) {}

int** Fichiers::lire(){
    std::ifstream fichier(chemin);
    
    if (!fichier.is_open()){
        throw std::runtime_error("Erreur : impossible d'ouvrir le fichier " + chemin);
    }
    
    std::string ligne;

    if (std::getline(fichier, ligne)){
        std::istringstream iss(ligne);
        if (!(iss >> lignes >> colonnes)){
            throw std::runtime_error("Erreur : format de dimensions invalide");
        }
    }else{
        throw std::runtime_error("Erreur : fichier vide");
    }

    int** grille = new int*[lignes];
    for (int i = 0; i < lignes; i++){
        grille[i] = new int[colonnes];
    }

    int ligne_actuelle = 0;
    
    while (std::getline(fichier, ligne) && ligne_actuelle < lignes){
        std::istringstream iss(ligne);
        for (int col = 0; col < colonnes; col++){
            if (!(iss >> grille[ligne_actuelle][col])){
                throw std::runtime_error("Erreur : donnée manquante à la ligne " + std::to_string(ligne_actuelle + 1));
            }
        }
        ligne_actuelle++;
    }

    if (ligne_actuelle != lignes){
        throw std::runtime_error("Erreur : nombre de lignes incohérent");
    }
    
    fichier.close();
    return grille;
}

int Fichiers::getLignes() const{
    return lignes;
}

int Fichiers::getColonnes() const{
    return colonnes;
}
