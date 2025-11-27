#pragma once
#include "Regles.hpp"

class Etat_cellule{
protected: 
	virtual ~Etat_cellule() = default;
	virtual bool estVivante() const = 0; 
	virtual Etat_cellule* determinerProchainEtat(int nbVoicins, const ReglesConway& regles) = 0; 
};
