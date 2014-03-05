#ifndef BAS
#define BAS

#include "Grille.hpp"
#include "Moteur.hpp"
#include "Algo.hpp"

/**
 * @class Base
 * classe contenant tous les objets necessaires au logiciel
 */
class Base{
	private:
	//	Moteur moteur;
		Algo algo;
		Grille grille;
		unsigned int pointActuel, niveauActuel;
	public:
		Base();
		void initJeu();
		void lancerJeu();
		void afficherEtatActuel()const;
		~Base();
};

#endif
