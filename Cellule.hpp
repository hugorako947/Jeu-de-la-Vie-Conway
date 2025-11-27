#pragma once
#include "Etat_cellule.hpp"

class ReglesConway;
class Grille;

class Cellule{
private: 
	int x; 
	int y; 
	Etat_cellule* etat; 
	Etat_cellule* prochainEtat;
public : 
	Cellule(int coordX, int coordY, Etat_cellule* etatInitial); 
	~Cellule();
	int get_x() const; 
	int get_y() const;
	int compterVoisinsVivants(const Grille& grille) const; //Calcule et retourne le nombre de cellules vivantes adjacentes à la cellule située aux coordonnées (x, y). 
	void definirEtat(Etat_cellule* nouvelEtat); //méthode
	void calculerProchainEtat(const Grille& grille, const ReglesConway& regles); // Méthode pour remplir 'prochainEtat'
	void appliquerProchainEtat(); // Méthode pour définir 'etat = prochainEtat'
	bool estVivante() const;
};
