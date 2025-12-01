#include "Grille.hpp"
#include <vector>
#include <string>
#include "Cellule.hpp"
#include <iostream> // Bien que non strictement nécessaire pour ces méthodes simples, il est conservé si besoin futur.

namespace JeuDeLaVie {
    // Implémentation du constructeur par défaut. 
    // La liste d'initialisation garantit que les booléens sont initialisés à false.
    Cellule::Cellule()
        : est_vivante(false), prochain_etat_vivant(false) {
    }

    // Retourne l'état actuel de la cellule.
    bool Cellule::estVivante() const {
        return est_vivante;
    }

    // Définit l'état actuel de la cellule à VIVANT.
    void Cellule::setEtatVivant() {
        est_vivante = true;
    }

    // Définit l'état actuel de la cellule à MORT.
    void Cellule::setEtatMort() {
        est_vivante = false;
    }

    // Calcule l'état de la prochaine génération en fonction de l'état actuel et des voisines.
    // Le résultat est stocké dans 'prochain_etat_vivant', sans affecter 'est_vivante'.
    void Cellule::calculerProchainEtat(int nb_voisines_vivantes) {
        // Initialiser l'état futur par défaut comme étant le même que l'état actuel
        prochain_etat_vivant = est_vivante;

        if (est_vivante) {
            // --- RÈGLES POUR UNE CELLULE VIVANTE ---

            // 1. Sous-population : moins de 2 voisines vivantes -> MEURT
            if (nb_voisines_vivantes < 2) {
                prochain_etat_vivant = false;
            }
            // 2. Survie : 2 ou 3 voisines vivantes -> SURVIT (prochain_etat_vivant reste le même, donc true)
            else if (nb_voisines_vivantes == 2 || nb_voisines_vivantes == 3) {
                // Pas de changement nécessaire, prochain_etat_vivant est déjà true
                // prochain_etat_vivant = true; 
            }
            // 3. Surpopulation : plus de 3 voisines vivantes -> MEURT
            else if (nb_voisines_vivantes > 3) {
                prochain_etat_vivant = false;
            }
        }
        else {
            // --- RÈGLES POUR UNE CELLULE MORTE ---

            // 4. Reproduction : exactement 3 voisines vivantes -> DEVIENT VIVANTE
            if (nb_voisines_vivantes == 3) {
                prochain_etat_vivant = true;
            }
            // Sinon, elle reste morte (pas de changement nécessaire)
        }
    }


    // Applique l'état calculé dans 'prochain_etat_vivant' à l'état actuel 'est_vivante'.
    void Cellule::appliquerProchainEtat() {
        // L'état actuel prend la valeur de l'état futur qui a été calculé.
        est_vivante = prochain_etat_vivant;
    }

} 
