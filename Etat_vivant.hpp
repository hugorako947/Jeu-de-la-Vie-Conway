#include "Etat_cellule.hpp"
#include "Regles.hpp"
class Etat_vivant : public Etat_cellule {
public: 
	~Etat_vivant() override = default; 
	bool estVivante() const override; //méthode héritée
	Etat_cellule* determinerProchainEtat(int nbVoisins, const ReglesConway& regles) override; //méthode hérité 
};
