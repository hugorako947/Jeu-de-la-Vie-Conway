#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>  // Pour std::find
#include <windows.h> // Pour l'utilisation de la fonction Sleep() ce qui gère les pauses entre chaque itérations
#include "Jeu.hpp"
#include "Fichiers.hpp"
#include "Grille.hpp"
#include "Cellule.hpp"
#include "EtatVivant.hpp"
#include "EtatMort.hpp"

Jeu::Jeu(std::string c, bool mc, int im, double p) : chemin(c), mode_console(mc), iterations_max(im), pause(p) {}

void Jeu::simulation(){
    try{
        JeuDeLaVie::Fichiers fichier(chemin);
        std::vector<int> donnees1D = fichier.lire();
        int lignes = fichier.getLignes();
        int colonnes = fichier.getColonnes();

        std::cout << "\nDEBUT DU JEU..." << std::endl;

        // 2. Créer un vecteur temporaire de cellules
        std::vector<JeuDeLaVie::Cellule> cellulesInitiales;
        cellulesInitiales.reserve(lignes * colonnes);

        // 3. Remplir les cellules selon les données du fichier
        for (int i = 0; i < lignes; i++){
            for (int j = 0; j < colonnes; j++){
                int index = i * colonnes + j;
                
                JeuDeLaVie::Cellule cellule;
                if (donnees1D[index] == 1){
                    cellule.setEtatVivant();
                } else {
                    cellule.setEtatMort();
                }
                cellulesInitiales.push_back(std::move(cellule));
            }
        }

        JeuDeLaVie::Grille grille(lignes, colonnes);
        grille.initialiser(cellulesInitiales);
        
        int iteration = 0;
        bool stable = false;
        
        while (true) {
            if (stable && iterations_max == 0){
                break;
            }
            
            if (iterations_max > 0 && iteration >= iterations_max + 1){
                break;
            }
            
            std::string etat_actuel = grille.afficher();
            if (mode_console){
                if (iteration != 0){
                    std::cout << "\nITERATION " << iteration << std::endl;
                }
                else{
                    std::cout << "\nETAT INITIAL" << std::endl;
                }
                std::cout << etat_actuel;
            }

            stable = stabilite(etat_actuel);
            
            historique.push_back(etat_actuel);
            
            grille.mettreAJour();
            
            iteration++;
            
            if (iteration <= iterations_max || iterations_max == 0){
                Sleep(static_cast<DWORD>(pause * 1000));
            }
        }
        
        std::cout << "\nFIN DU JEU...\n" << std::endl;
        std::cout << "Nombre d'iterations: " << iteration-1 << std::endl;
        
        if (stable && iterations_max == 0){
            std::cout << "Raison: grille stable (plus d'evolution)" << std::endl;
        }else if (iterations_max > 0){
            std::cout << "Raison: nombre maximum d'iterations atteint" << std::endl;
        }
        std::cout << "" << std::endl;
        
    }
    catch (const std::exception& e){
        std::cerr << "Erreur dans la simulation : " << e.what() << std::endl;
        std::cout << "" << std::endl;
    }
}

bool Jeu::stabilite(const std::string& etat_actuel){
    if (historique.empty()){
        return false;
    }

    if (historique.back() == etat_actuel){
        return true;
    }

    for (size_t i = 0; i < historique.size() - 1; i++){
        if (historique[i] == etat_actuel) {
            return true;
        }
    }
    
    return false;
}
