#ifndef GRI
#define GRI

#include "Case.hpp"
#include <vector>
#include <list>

class Algo;

/**
 * @class Grille
 * classe de gestion et de stock de la grille
 */
class Grille{
	private:
		Algo *memAlgo;
		std::vector<std::vector<Case>> tabGrille;
		unsigned int largeurG, longueurG, hauteurG;
	public:
		Grille();
		void genererGrille(unsigned int lvl);
		bool appliquerChangeCase(unsigned int x, unsigned int y);
		void afficherGrille()const;
		const std::vector<std::vector<Case>> *getTab()const;
		unsigned int getTabValue(unsigned int x, unsigned int y)const;
		~Grille();
};

#endif
