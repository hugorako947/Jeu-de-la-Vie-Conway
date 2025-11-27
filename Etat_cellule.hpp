//Pattern d'État??? voir plus tard pour les explications 
#include "Regles.hpp"
class Etat_cellule {
protected: 
	virtual ~Etat_cellule() = default;
	virtual bool estVivante() const = 0; 
	virtual Etat_cellule* determinerProchainEtat(int nbVoicins, const ReglesConway& regles) = 0; 
};
