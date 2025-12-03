#include "Fichier.hpp"
#include <string>
#include <sstream>

namespace JeuDeLaVie {
    Fichiers::Fichiers(std::string c) : chemin(c), lignes(0), colonnes(0) {}

    std::vector<int> Fichiers::lire() {
        std::ifstream fichier(chemin);
        std::vector<int> donnees_1d;

        if (!fichier.is_open()) {
            throw std::runtime_error("ERREUR : Impossible d'ouvrir le fichier " + chemin + " !\n");
        }

        std::string ligne;

        if (std::getline(fichier, ligne)) {
            std::istringstream iss(ligne);
            if (!(iss >> lignes >> colonnes)) {
                throw std::runtime_error("ERREUR : Dimensions de la grille incoherentes !\n");
            }
        }
        else {
            throw std::runtime_error("ERREUR : Fichier vide !\n");
        }

        int total_cells = lignes * colonnes;
        int cells_read = 0;
        int etat_cellule;

        while (fichier >> etat_cellule && cells_read < total_cells) {
            if (etat_cellule != 0 && etat_cellule != 1) {
                throw std::runtime_error("ERREUR : Donnee de cellule invalide !\n");
            }
            donnees_1d.push_back(etat_cellule);
            cells_read++;
        }
        if (cells_read != total_cells) {
            throw std::runtime_error("ERREUR : Nombre total de cellules incoherent ! Attendu : " + std::to_string(total_cells) + ", Lu : " + std::to_string(cells_read) + "\n");
        }
        fichier.close();
        return donnees_1d;
    }
    void Fichiers::ecrire(const std::string etat, int iteration) const {
        if (lignes == 0 || colonnes == 0) return;

        // EXTRACTION DU NOM DE BASE 
        const std::string& chemin_complet = chemin;
        size_t pos_slash = chemin_complet.find_last_of("/\\");
        std::string nom_avec_ext = (pos_slash == std::string::npos) ? chemin_complet : chemin_complet.substr(pos_slash + 1);
        size_t pos_point = nom_avec_ext.find_last_of('.');

        std::string nom_fichier_base;
        if (pos_point == std::string::npos) {
            nom_fichier_base = nom_avec_ext;
        }
        else {
            nom_fichier_base = nom_avec_ext.substr(0, pos_point);
        }
        // 2. Définir le chemin du dossier de sortie
        std::string nom_dossier_out = nom_fichier_base + "_out";

        // 3. Définir le nom du fichier de sortie (simple concaténation)
        std::string num_iteration_str = std::to_string(iteration);
        std::string chemin_fichier_out = nom_dossier_out + "/" + num_iteration_str + ".txt";

        std::ofstream fichier_out(chemin_fichier_out);

        if (!fichier_out.is_open()) {
            std::cerr << "AVERTISSEMENT: Impossible d'ouvrir le fichier de sortie: " << chemin_fichier_out << std::endl;
            return;
        }
        fichier_out << lignes << " " << colonnes << "\n";
        fichier_out << etat; 
        fichier_out.close();
    }
    int Fichiers::getLignes() const {
        return lignes;
    }

    int Fichiers::getColonnes() const {
        return colonnes;
    }
}
