#include <iostream>
#include <vector>
#include <memory>
#include <windows.h> // Pour la fonction Sleep()
#include "Jeu.hpp"
#include "Fichier.hpp"
#include "Grille.hpp"
#include "Cellule.hpp"
#include "EtatVivant.hpp"
#include "EtatMort.hpp"
#include "Tests.hpp"

Jeu::Jeu(std::string ci, bool mc, int im, double p, std::string co) : chemin_input(ci), mode_console(mc), iterations_max(im), pause(p), chemin_output(co) {}

void Jeu::simulation(){
    try{
        JeuDeLaVie::Fichiers fichier(chemin_input, chemin_output);
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
            if (stable){
                break;
            }
            
            if (iteration == iterations_max + 1){
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
                fichier.ecrire(etat_actuel, iteration);
            }

            stable = stabilite(etat_actuel);
            
            historique.push_back(etat_actuel);
            
            grille.mettreAJour();
            
            iteration++;
            
            Sleep(static_cast<DWORD>(pause * 1000));
        }

        std::cout << "\nFIN DU JEU...\n" << std::endl;
        std::cout << "Nombre d'iterations: " << iteration-1 << std::endl;
        if (stable && iteration == iterations_max + 1){
            std::cout << "Raison: grille stable (plus d'evolution) + nombre maximum d'iterations atteint\n" << std::endl;
        }
        else if (stable && iteration < iterations_max + 1){
            std::cout << "Raison: grille stable (plus d'evolution)\n" << std::endl;
        }
        else if (!stable && iteration == iterations_max + 1){
            std::cout << "Raison: nombre maximum d'iterations atteint\n" << std::endl;
        }
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

void Jeu::tests_unitaires() {
    try {
        std::cout << "\nDEBUT DES TESTS...\n" << std::endl;
        
        JeuDeLaVie::TestsUnitaires grille_vide("tests/grille_vide_depart.txt", "tests/grille_vide_depart.txt", 5);
        JeuDeLaVie::TestsUnitaires bloc_stable("tests/bloc_stable_depart.txt", "tests/bloc_stable_depart.txt", 10);
        JeuDeLaVie::TestsUnitaires clignotant1("tests/clignotant_depart.txt", "tests/clignotant_attendu.txt", 1);
        JeuDeLaVie::TestsUnitaires clignotant2("tests/clignotant_attendu.txt", "tests/clignotant_depart.txt", 1);
        JeuDeLaVie::TestsUnitaires planeur("tests/planeur_depart.txt", "tests/planeur_attendu.txt", 4);

        std::cout << "\nFIN DES TESTS...\n" << std::endl;
        double pourcentage = planeur.getTestsValides() / planeur.getTotalTests() * 100;
        if (planeur.getTestsValides() == planeur.getTotalTests()){
            std::cout << "Tests reussis: " << planeur.getTestsValides() << "/" << planeur.getTotalTests() << " (" << pourcentage << " %)" << " => Les regles de Conway sont correctement implementees.\n" << std::endl;
        }
        else{
            std::cout << "Tests reussis: " << planeur.getTestsValides() << "/" << planeur.getTotalTests() << " (" << pourcentage << " %)" << " => Les regles de Conway sont mal implementees.\n" << std::endl;
        }
    }
    catch (const std::exception& e){
        std::cerr << "\nErreur dans les tests: " << e.what() << std::endl;
    }
}
