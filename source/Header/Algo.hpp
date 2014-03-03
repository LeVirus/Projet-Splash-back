#ifndef ALG
#define ALG

#include <vector>
#include "Case.hpp"

class Grille;
class Case;

/**                                                                    
 * @struct DestinationBulle
 *Structure de memorisation et de gestion des evenements de la grille
 */
struct DestinationBulle{
	unsigned int temps, direction, coX, coY;
	bool traite;
};

/**
 * @struct OrigineEclatement
 *Structure de memorisation de l'origine des eclatements
 */
struct OrigineEclatement{
	unsigned int coXO, coYO, tempsO;                                     
};

class Algo{
	private:
		Grille *memoG;
		std::vector<std::vector<Case>> *memTabGrille;
		std::list<*OrigineEclatement> memOrigineEclat;
		std::list<*OrigineEclatement>::iterator itMemOrigin;
		std::list<*DestinationBulle> memDestinationBulle;
		std::list<*DestinationBulle>::iterator itMemBulle;
	public:
		Algo();
void resolutionEclatement(unsigned int x, unsigned int y);
		void jouer();
		void resolution();
void trouverDestination(unsigned int x, unsigned int y);
		~Algo();
};


#endif
