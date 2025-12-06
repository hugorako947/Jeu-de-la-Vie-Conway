#include <iostream>
#include <stdexcept>
#include "Fichier.hpp"
#include <string>
#include <sstream>
 
namespace JeuDeLaVie {
    Fichiers::Fichiers(std::string ci, std::string co) : chemin_input(ci), chemin_output(co), lignes(0), colonnes(0) {}
    
    std::vector<int> Fichiers::lire(){
        std::ifstream fichier(chemin_input);
        std::vector<int> donnees_1d;
    
        if (!fichier.is_open()){
            throw std::runtime_error("ERREUR: Impossible d'ouvrir le fichier " + chemin_input + " !\n");
        }

        std::string ligne;

        if (std::getline(fichier, ligne)){
            std::istringstream iss(ligne);
            if (!(iss >> lignes >> colonnes)){
                throw std::runtime_error("ERREUR: Dimensions de la grille incoherentes !\n");
            }
        }else{
            throw std::runtime_error("ERREUR: Fichier vide !\n");
        }

        int total_cells = lignes * colonnes;
        int cells_read = 0;
        int etat_cellule;

        while (fichier >> etat_cellule && cells_read < total_cells){
            if (etat_cellule != 0 && etat_cellule != 1){
                throw std::runtime_error("ERREUR: Donnee de cellule invalide !\n");
            }
            donnees_1d.push_back(etat_cellule);
            cells_read++;
        }
        if (cells_read != total_cells){
            throw std::runtime_error("ERREUR: Nombre total de cellules incoherent ! Attendu : " + std::to_string(total_cells) + ", Lu : " + std::to_string(cells_read) + "\n");
        }
        fichier.close();
        return donnees_1d;
    }

    void Fichiers::ecrire(const std::string& etat, int iteration) const{
        if (lignes == 0 || colonnes == 0) return;

        std::string nom_base;
        size_t pos_slash = chemin_input.find_last_of("/\\");
        if (pos_slash == std::string::npos){
            nom_base = chemin_input;  // Pas de chemin, c'est déjà le nom
        }
        else{
            nom_base = chemin_input.substr(pos_slash + 1);
        }
        
        // Enlever l'extension .txt du fichier de base dans le dossier input si elle existe
        size_t pos_point = nom_base.find_last_of('.');
        if (pos_point != std::string::npos){
            nom_base = nom_base.substr(0, pos_point);
        }
        std::string nom_fichier = nom_base + "_out" + std::to_string(iteration) + ".txt";
        
        // Création d'un fichier txt
        std::ofstream fichier_out(chemin_output + nom_fichier);

        // Gérer l'erreur de création d'un fichier [nom du fichier de base]_out1.txt dans le dossier output
        if (!fichier_out.is_open()){
            std::cerr << "ERREUR: Impossible de creer le fichier " << nom_fichier << " !" << std::endl;
            return;
        }
        
        // Écrire dans la grille
        fichier_out << lignes << " " << colonnes << std::endl;
        fichier_out << etat;
        fichier_out.close();
        std::cout << "Fichier: " << nom_fichier << std::endl;
    }

    int Fichiers::getLignes() const {
        return lignes;
    }

    int Fichiers::getColonnes() const {
        return colonnes;
    }
}
