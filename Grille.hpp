#include "Cellule.hpp"
#include <vector>
#include <string>
class Grille {
private: 
	int lignes; 
	int colonnes; 
	std::vector<Cellule*> cellules;//tableau dynamique qui va stocker l'état de chaque cellule de la grille 
public: 
	Grille(int l, int c);
	int get_l() const; 
	int get_c() const; 
	void initialiser(const std::vector<Cellule*>& g); //méthode pour remplir la grille avec des états de cellules initiaux (config de depart)
	void mettreAJour(); //Applique les règles du jeu pour calculer et appliquer le nouvel état de la grille 
	std::string exporterEtat();//Retourne une représentation de l'état actuel de la grille
	Cellule* getCellule(int x, int y) const;
};
