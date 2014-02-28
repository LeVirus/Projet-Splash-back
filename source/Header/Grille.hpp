#ifndef GRI
#define GRI

#include "Case.hpp"
#include <vector>
#include <list>

/**
* @struct ActionBulle
*Structure de memorisation et de gestion des evenements de la grille
*/
struct ActionBulle{
	unsigned int temps, direction, coX, coY;
};

/**
 * @class Grille
 * classe de gestion et de stock de la grille
 */
class Grille{
	private:
		std::list<ActionBulle> memActionBulle;
		std::vector<std::vector<Case>> tabGrille;
		unsigned int largeurG, longueurG, hauteurG;
	public:
		Grille();
		void genererGrille(unsigned int lvl);
		void resolutionEclatement(unsigned int x, unsigned int y);
		bool appliquerChangeCase(unsigned int x, unsigned int y);
		void afficherGrille();
		~Grille();
};

#endif
