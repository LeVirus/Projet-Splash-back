#ifndef CAS
#define CAS

/**
 * @class Case
 * classe definissant toutes les actions possibles d'une bulle
 * Ou d'une case vide
 */
class Case{
	private: 
		unsigned int etat;
		bool eclater;
	public:
		Case();
		Case(unsigned int taille);
		void setEtat(unsigned int nbr);
		bool changerEtat();
		unsigned int getEtat();
		bool eclater();
		~Case();
};

#endif
