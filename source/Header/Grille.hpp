#ifndef GRI
#define GRI

#include "Case.hpp"
#include <vector>
/**
 * @class Grille
 * classe de gestion et de stock de la grille
 */
class Grille{
	private:
		std::vector<std::vector<Case>> tabGrille;
		unsigned int largeurG, longueurG, hauteurG;
	public:
		Grille();
		void genererGrille(unsigned int lvl);
		bool appliquerClick(unsigned int x, unsigned int y);
		void afficherGrille();
		~Grille();
};

#endif
