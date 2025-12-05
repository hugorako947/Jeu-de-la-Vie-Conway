#include "Cellule.hpp"
#include "EtatMort.hpp" 
#include "Etatvivant.hpp"
#include "Etat_Cellule.hpp"
#include <memory>

namespace JeuDeLaVie {

    // CONSTRUCTEUR
    // Initialise la cellule par défaut à l'état Mort.
    Cellule::Cellule() : etat_actuel(std::make_unique<EtatMort>()), prochain_etat(nullptr) {} // Utilise std::make_unique pour créer le premier objet d'état // L'état futur est initialisé à null

    // Constructeur par déplacement
    Cellule::Cellule(Cellule&& autre) noexcept
        : etat_actuel(std::move(autre.etat_actuel)),
          prochain_etat(std::move(autre.prochain_etat)) {
    }

    // Opérateur d'affectation par déplacement
    Cellule& Cellule::operator=(Cellule&& autre) noexcept {
        if (this != &autre) {
            etat_actuel = std::move(autre.etat_actuel);
            prochain_etat = std::move(autre.prochain_etat);
        }
        return *this;
    }

    // ACCESSEURS
    // Délègue la vérification de l'état à l'objet d'état actuel (polymorphisme).
    bool Cellule::estVivante() const {
        // Si etat_actuel est nullptr (ne devrait pas arriver), on retourne false
        if (!etat_actuel) {
            return false;
        }
        return etat_actuel->estVivante();
    }

    // MUTATEURS (Utilisés principalement pour l'initialisation par la classe Jeu)
    void Cellule::setEtatVivant() {
        // Création d'un nouvel objet EtatVivant et remplacement de l'état actuel.
        // L'ancien état (EtatMort) est automatiquement détruit par unique_ptr.
        etat_actuel = std::make_unique<EtatVivant>();
    }

    void Cellule::setEtatMort() {
        // Création d'un nouvel objet EtatMort.
        etat_actuel = std::make_unique<EtatMort>();
    }

    // LOGIQUE DE MISE À JOUR (Étape 1 : Calcul)
    // Délègue la logique des règles à l'objet d'état actuel.
    void Cellule::calculerProchainEtat(int nb_voisins) {
        if (!etat_actuel) return; // Sécurité

        // L'objet d'état actuel détermine et crée le nouvel état nécessaire.
        // Le std::unique_ptr est assigné à prochain_etat, qui en prend la propriété.
        prochain_etat = etat_actuel->determinerProchainEtat(nb_voisins);
    }

    // LOGIQUE DE MISE À JOUR (Étape 2 : Transition)
    void Cellule::appliquerProchainEtat() {
        if (!prochain_etat) return; // Sécurité

        // L'état actuel prend la propriété de l'état futur (move semantics).
        // L'ancien objet pointé par etat_actuel (avant le move) est détruit.
        etat_actuel = std::move(prochain_etat);

        // prochain_etat est maintenant nullptr après le move.
    }

} // Fin du namespace JeuDeLaVie
