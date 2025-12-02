#include "Grille.hpp"
#include "Cellule.hpp"
#include <stdexcept>
#include <string>
#include <algorithm> // Gardé pour std::copy, mais n'est pas utilisé dans initialiser

namespace JeuDeLaVie {

    // FONCTION UTILITAIRE (Interne)
    // Index 1D = (ligne * nombre_de_colonnes) + colonne
    static int getIndex(int l, int c, int nb_c) {
        return l * nb_c + c;
    }

    // CONSTRUCTEUR

    Grille::Grille(int l, int c) : lignes(l), colonnes(c) {
        if (l > 0 && c > 0) {
            cellules.resize(lignes * colonnes);
        }
        else {
            lignes = 0;
            colonnes = 0;
        }
    }

    // ----------------------------------------------------------------------
    // GETTERS & ACCESSEURS
    // ----------------------------------------------------------------------

    int Grille::get_l() const {
        return lignes;
    }

    int Grille::get_c() const {
        return colonnes;
    }
    //getter pas constant pour les modifications 
    Cellule& Grille::get_cellule(int l, int c) {
        return cellules.at(getIndex(l, c, colonnes));
    }
    //getter constant sans modification 
    const Cellule& Grille::get_cellule(int l, int c) const {
        return cellules.at(getIndex(l, c, colonnes));
    }

  
//méthode pour initialiser la grille 
    void Grille::initialiser(const std::vector<Cellule>& g) {
        if (g.size() == cellules.size()) {
            // Créez une copie de travail modifiable
            std::vector<Cellule> temp_g = g;

            // Déplacez chaque élément de temp_g vers cellules
            for (size_t i = 0; i < cellules.size(); ++i) {
                cellules[i] = std::move(temp_g[i]); 
            }
        }
    }

    std::string Grille::afficher() const {
        std::string resultat = "";
        for (int l = 0; l < lignes; ++l) {
            for (int c = 0; c < colonnes; ++c) {
                const Cellule& cell = get_cellule(l, c);
                resultat += cell.estVivante() ? "█ " : "░ ";
            }
            resultat += "\n";
        }
        return resultat;
    }

    int Grille::compterVoisinesVivantes(int l, int c) const {
        int count = 0;
        for (int l_voisine = l - 1; l_voisine <= l + 1; ++l_voisine) {
            for (int c_voisine = c - 1; c_voisine <= c + 1; ++c_voisine) {

                if (l_voisine == l && c_voisine == c) {
                    continue;
                }

                if (l_voisine >= 0 && l_voisine < lignes && c_voisine >= 0 && c_voisine < colonnes) {
                    const Cellule& voisine = get_cellule(l_voisine, c_voisine);
                    if (voisine.estVivante()) {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    // MISE À JOUR (Compatible avec Pattern d'État et Polymorphisme)
    void Grille::mettreAJour() {
        // Étape 1 : Calculer le prochain état
        for (int l = 0; l < lignes; ++l) {
            for (int c = 0; c < colonnes; ++c) {
                Cellule& cellule_actuelle = get_cellule(l, c);
                int voisines = compterVoisinesVivantes(l, c);

                cellule_actuelle.calculerProchainEtat(voisines);
            }
        }

        // Étape 2 : Appliquer la transition
        for (int l = 0; l < lignes; ++l) {
            for (int c = 0; c < colonnes; ++c) {
                Cellule& cellule_actuelle = get_cellule(l, c);
                cellule_actuelle.appliquerProchainEtat();
            }
        }
    }

} 
