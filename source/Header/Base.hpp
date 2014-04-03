#ifndef BASE
#define BASE

#include "Grille.hpp"
#include "Moteur.hpp"
#include "Algo.hpp"

/**
 * @class Base
 * classe contenant tous les objets necessaires au logiciel
 */
class Base{
	private:
		Algo algo;
		Grille grille;
		Moteur moteur;
		unsigned int niveauActuel;
	public:
		Base();
		void initJeu();
		void lancerJeu();
		void afficherEtatActuel()const;
		~Base();
};

#endif
