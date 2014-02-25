#include "Grille.hpp"
#include "Moteur.hpp"

class Base{
	private:
		Grille grille;
		Moteur moteur;
		unsigned int pointActuel, largeurG, longueurG, hauteurG;
	public:
		Base();
		afficherGrille();
		~Base();
};
