#ifndef ALG
#define ALG

#include <iostream>
#include <vector>
#include <list>
#include "Case.hpp"

class Grille;

/**                                                                    
 * @struct DestinationBulle
 * Structure de memorisation de la destination d'une bulle mouvante
 * contient le temps d'arrivée la direction et les coordonnées d'arrivée
 */
struct DestinationBulle{
	unsigned int temps, direction, coX, coY;
	bool traite;
};

/**
 * @struct OrigineEclatement
 * Structure de memorisation de l'origine des eclatements
 * (origine des bulles mouvantes)
 * contient le temps et les coordonnées de déclenchement
 */
struct OrigineEclatement{
	unsigned int coXO, coYO, tempsO;                                     
};


/**
 * @struct AnimList
 * Structure contenant les 2 listes nécessaires à la mémorisation
 * des animations d'éclatements
 */
struct AnimList{
	std::list<OrigineEclatement*> *memListOrigine;
	std::list<DestinationBulle*> *memListDestination;
};

/**
 * @class Algo 
 * Classe de gestion algorithmique des éclatements
 * Calcul et mémorisations des animations
 */
class Algo{
	private:
		Grille *memoG;
		unsigned int memoTempsEclat, coupsRestants;
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
