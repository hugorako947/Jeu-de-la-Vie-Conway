#include <iostream>
#include "Tests.hpp"
#include "Fichier.hpp"
#include "Grille.hpp"
#include "Cellule.hpp"
#include <iostream>
#include <fstream>
#include <vector>

namespace JeuDeLaVie{

    double TestsUnitaires::total_tests = 0;
    double TestsUnitaires::tests_valides = 0;

    TestsUnitaires::TestsUnitaires(std::string fd, std::string fa, int i) : fichier_depart(fd), fichier_attendu(fa), iterations(i) {
        total_tests++;
        if (estValide()){
            std::cout << "[OK] "<< fichier_depart << " fonctionne bien (" << iterations << " iteration(s))" << std::endl;
            tests_valides++;
        }
        else{
            std::cout << "[ECHEC] Grille vide" << std::endl;
        }
    }
    
    bool TestsUnitaires::estValide(){
        try{
            // 1. Charger la grille de départ
            Fichiers fichier_depart_obj(fichier_depart, "");
            std::vector<int> donnees_depart = fichier_depart_obj.lire();
            int lignes = fichier_depart_obj.getLignes();
            int colonnes = fichier_depart_obj.getColonnes();
            
            // Convertir en Cellules
            std::vector<Cellule> cellules_depart;
            cellules_depart.reserve(lignes * colonnes);
            
            for (int i = 0; i < lignes; i++){
                for (int j = 0; j < colonnes; j++){
                    int index = i * colonnes + j;
                    Cellule cellule;
                    if (donnees_depart[index] == 1){
                        cellule.setEtatVivant();
                    } else {
                        cellule.setEtatMort();
                    }
                    cellules_depart.push_back(std::move(cellule));
                }
            }
            
            // Créer la grille
            Grille grille(lignes, colonnes);
            grille.initialiser(cellules_depart);
            
            // 2. Exécuter les itérations
            for (int i = 0; i < iterations; i++){
                grille.mettreAJour();
            }
            
            // 3. Charger la grille attendue
            Fichiers fichier_attendu_obj(fichier_attendu, "");
            std::vector<int> donnees_attendu = fichier_attendu_obj.lire();
            int lignes_attendu = fichier_attendu_obj.getLignes();
            int colonnes_attendu = fichier_attendu_obj.getColonnes();
            
            // Vérifier les dimensions
            if (lignes != lignes_attendu || colonnes != colonnes_attendu){
                return false;
            }
            
            // Convertir en Cellules pour comparaison
            std::vector<Cellule> cellules_attendu;
            cellules_attendu.reserve(lignes * colonnes);
            
            for (int i = 0; i < lignes; i++){
                for (int j = 0; j < colonnes; j++){
                    int index = i * colonnes + j;
                    Cellule cellule;
                    if (donnees_attendu[index] == 1){
                        cellule.setEtatVivant();
                    } else {
                        cellule.setEtatMort();
                    }
                    cellules_attendu.push_back(std::move(cellule));
                }
            }
            
            // 4. Comparer les deux grilles
            Grille grille_attendu(lignes, colonnes);
            grille_attendu.initialiser(cellules_attendu);
            
            // Comparer cellule par cellule
            for (int i = 0; i < lignes; i++) {
                for (int j = 0; j < colonnes; j++) {
                    if (grille.get_cellule(i, j).estVivante() != 
                        grille_attendu.get_cellule(i, j).estVivante()){
                        return false;
                    }
                }
            }
            return true;
            
        }
        catch (const std::exception& e){
            std::cerr << "Erreur dans le test " << fichier_depart << ": " << e.what() << std::endl;
            return false;
        }
    }

    double TestsUnitaires::getTotalTests(){
        return total_tests;
    }

    double TestsUnitaires::getTestsValides(){
        return tests_valides;
    }
}
