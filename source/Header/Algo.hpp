#ifndef ALG
#define ALG

#include <iostream>
#include <vector>
#include <list>
#include "Case.hpp"

class Grille;

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


struct AnimList{
	std::list<OrigineEclatement*> *memListOrigine;
	std::list<DestinationBulle*> *memListDestination;
};

class Algo{
	private:
		Grille *memoG;
		unsigned int memoTempsEclat;
		std::list<OrigineEclatement*> memOrigineEclat;
		std::list<OrigineEclatement*>::iterator itMemOrigin, itMemOriginB;
		std::list<DestinationBulle*> memDestinationBulle;
		std::list<DestinationBulle*>::iterator itMemBulle, itMemBulleB;
	public:
		Algo();
		void resolutionEclatement(unsigned int x, unsigned int y);
		std::list<OrigineEclatement*>::iterator findItEclat(unsigned int x, unsigned int y);
		void jouer();
		void liaisonGrille();
		void trouverDestination(unsigned int x, unsigned int y);
		void appliquerDestination();
		const	AnimList getListAnim();
		void afficherList()const;
		void viderListes();
		void corrigerDestinationBulle(DestinationBulle *a);
		~Algo();
};


#endif
