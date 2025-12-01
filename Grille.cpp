#include "Grille.hpp"
#include "ReglesConway.hpp"
#include <vector>
#include <string>
namespace JeuDeLaVie {
	//constructeur avec paramètre 
	Grille::Grille(int l, int c) : lignes(l), colonnes(c) {
		if (l > 0 && c > 0) { //creer le tableau en 2D et plus en 1D du vecteur 
			cellules.resize(lignes * colonnes);
		}
		else { //pour gerer les erreurs 
			lignes = 0; 
			colonnes = 0;
		}
	}
	//Getter 
	int Grille::get_l() const {
		return lignes;
	}
	int Grille::get_c() const {
		return colonnes;
	}
	//fonction utilitaire propre au grille.cpp
	//Index 1D = (ligne * nombre_de_colonnes) + colonne
	int getIndex(int l, int c, int nb_c) {
		return l * nb_c + c;
	}
	//getter de cellule pas constante (pour la modification) 
	Cellule& Grille::get_cellule(int l, int c) {
		return cellules.at(getIndex(l, c, colonnes));
	}
	// Version CONSTANTE (pour la lecture/observation)
	const Cellule& Grille::get_cellule(int l, int c) const {
		return cellules.at(getIndex(l, c, colonnes));
	}
	//méthode pour initialiser la grille en fonction de la config donnée par le joueur 
	void Grille::initialiser(const std::vector <Cellule>& g) {
		if (g.size() <= cellules.size()) {
			for (size_t i = 0; i < g.size(); ++i) {
				cellules[i] = g[i];
			}
		}
	}
	//méthode pour afficher la grille 
	std::string Grille::afficher() const {
		// Utilisation directe de std::string pour accumuler le résultat
		std::string resultat = "";

		// Parcourt la grille ligne par ligne
		for (int l = 0; l < lignes; ++l) {
			for (int c = 0; c < colonnes; ++c) {

				// Accède à la cellule en utilisant l'accesseur constant
				const Cellule& cell = get_cellule(l, c);

				// Si Cellule a une méthode 'estVivante()'
				if (cell.estVivante()) {
					resultat += "1 "; // Ajout d'une cellule vivante
				}
				else {
					resultat += "0"; // Ajout d'une cellule morte
				}
			}
			resultat += "\n"; // Ajout d'un retour à la ligne à la fin de chaque ligne de la grille
		}
		return resultat;
	}
    // Compte le nombre de voisines vivantes pour la cellule (l, c)
    int Grille::compterVoisinesVivantes(int l, int c) const {
        int count = 0;//on initialise le compteur à 0 
        // Parcourt les 8 voisines (l_voisine varie de l-1 à l+1, c_voisine varie de c-1 à c+1)
        for (int l_voisine = l - 1; l_voisine <= l + 1; ++l_voisine) {
            for (int c_voisine = c - 1; c_voisine <= c + 1; ++c_voisine) {

                // 1. Éviter de compter la cellule elle-même
                if (l_voisine == l && c_voisine == c) {
                    continue;
                }

                // 2. Vérifier les limites de la grille (éviter le débordement)
                if (l_voisine >= 0 && l_voisine < lignes && c_voisine >= 0 && c_voisine < colonnes) {

                    // 3. Accéder à la cellule voisine (on utilise l'accesseur constant)
                    const Cellule& voisine = get_cellule(l_voisine, c_voisine);

                    // 4. Compter si la voisine est vivante
                    if (voisine.estVivante()) {
                        count++;
                    }
                }
                // Note : Pour les règles de Conway classiques, les bords sont fermés
            }
        }
        return count;
    }

    // RÈGLES DU JEU : MISE À JOUR (ÉTAPE CRUCIALE)
    void Grille::mettreAJour() {
        // CRUCIAL : Créer une grille temporaire pour stocker les nouveaux états
        // Cela permet de calculer le nouvel état de TOUTES les cellules 
        // en utilisant uniquement l'état ACTUEL de la grille, évitant ainsi des mises à jour partielles.
        std::vector<Cellule> prochaine_generation(lignes * colonnes);//on vient créer un tableau dynamique pour stocker les nouveaux états des cellules 
        //Parcourir chaque cellule de la grille actuelle
        for (int l = 0; l < lignes; ++l) {
            for (int c = 0; c < colonnes; ++c) {
                // Obtenir la cellule actuelle (lecture)
                const Cellule& actuelle = get_cellule(l, c);
                // Calculer le nombre de voisines vivantes
                int voisines = compterVoisinesVivantes(l, c);
                // Obtenir l'index 1D pour la grille temporaire
                int index = getIndex(l, c, colonnes);
                // Initialiser la cellule de la prochaine génération avec l'état actuel
                prochaine_generation[index] = actuelle;

                // 2. Appliquer les règles de Conway
                if (actuelle.estVivante()) {
                    // Règle 1 & 2 : Surpopulation et Sous-population
                    if (voisines < 2 || voisines > 3) {
                        prochaine_generation[index].setEtatMort(); // Meurt
                    }
                    // Règle 3 : Survit si elle a 2 ou 3 voisines (pas besoin d'action ici
                }
                else {
                    // Règle 4 : Repopulation
                    if (voisines == 3) {
                        prochaine_generation[index].setEtatVivant(); // Revient à la vie
                    }
                }
            }
        }

        // 3. Appliquer la prochaine génération à la grille actuelle
        cellules = std::move(prochaine_generation);
    }
}
