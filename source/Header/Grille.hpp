#ifndef GRI
#define GRI

#include "Case.hpp"
#include <vector>
#include <list>

class Algo;

/**
 * @struct MemRes
 * Structure de mémorisation des cases a éclater pour la résolution
 * automatique
 */
struct MemRes{
	unsigned int X, Y, coupsN;
};


struct RetourResol{
	unsigned int note;
		std::list<MemRes*> *lstMem;

};

/**
 * @class Grille
 * classe de gestion et de stock de la grille
 */
class Grille{
	private:
		Algo *memAlgo;
		std::vector<std::vector<Case>> tabGrille, resolTabGrille;
		unsigned int largeurG, longueurG, hauteurG;
	public:
		Grille();
		void genererGrille(unsigned int lvl);
		bool appliquerChangeCase(unsigned int x, unsigned int y);
		void resolv(unsigned int x, unsigned int y);
std::vector<std::vector<Case>> *copieTabResolv();
		RetourResol *recursFind(unsigned int x, unsigned int y, unsigned int coupsRestants);
		void afficherGrille()const;
		void restoreGrille(std::vector<std::vector<Case>> *memG);
		const std::vector<std::vector<Case>> &getTabGrille()const;
		const std::vector<std::vector<Case>> *getTab()const;
		void resolv();
		unsigned int getTabValue(unsigned int x, unsigned int y)const;
		MemRes* findCase(unsigned int x, unsigned int y, unsigned int direction);
		~Grille();
};

#endif
