#include "Case.hpp"
#include "Grille.hpp"

extern Grille *memGrille;

/**
 * Constructeur par défaut de la classe Case.
 * etat mis à 0
 */
Case::Case(){
	etat=0;
}

/**
 * Constructeur de la classe Case.
 * @param taille : l'etat initial de la case créée 
 */
Case::Case(unsigned int taille){
	if(etat>4)etat=4;
	else {
		etat=taille;
	}
}

/**
 * Fonction permettant de modifier l'état de la bulle
 * @param nbr : La nouvelle valeur de la bulle
 */
void Case::setEtat(unsigned int nbr){
	etat=nbr;
}

/**
 * Change l'etat de la case si l'etat depasse la valeur max la fonction eclater() est appelée
 * @return false si la bulle n'eclate pas
 * @return true sinon
 */
bool Case::changerEtat(){
	etat++;
	if(etat>4){
		etat=0;
		return true;
	}
	return false;
}

/**
 * Retourne l'etat de la bulle
 * @return Case.etat l'etat actuel de la case(taille bulle)
 */
unsigned int Case::getEtat()const{
	return etat;
}

/**
 * Destructeur de la class Case.  
 */
Case::~Case(){

}
