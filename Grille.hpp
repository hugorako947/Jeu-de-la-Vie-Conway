#pragme once
#include "Cellule.hpp"
#include <vector>
#include <string>
namespace JeuDeLaVie {
	class Grille {
	private:
		int lignes;
		int colonnes;
		std::vector<Cellule> cellules;//tableau dynamique qui va stocker l'état de chaque cellule de la grille 
	public:
		Grille(int l, int c);
		int get_l() const;
		int get_c() const;
		void initialiser(const std::vector<Cellule>& g); //méthode pour remplir la grille avec des états de cellules initiaux (config de depart) 
		Cellule& get_cellule(int l, int c);
		const Cellule& get_cellule(int l, int c) const;
		int compterVoisinesVivantes(int l, int c) const;
		std::string afficher() const;
		void mettreAJour();
	};
}
