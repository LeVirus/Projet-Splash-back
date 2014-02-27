#include "Case.hpp"

/**
 * Constructeur par défaut de la classe Case.
 * etat mis à 0
 */
Case::Case(){
	etat=0;
}

/**
 * Constructeur de la classe Case.
 * @param taille l'etat initial de la case créée 
 */
Case::Case(unsigned int taille){
	if(etat>4)etat=4;
	else {
		etat=taille;
	}
}

/**
 * Fonction permettant de modifier l'état de la bulle
 * @param nbr La nouvelle valeur de la bulle
 */
void Case::setEtat(unsigned int nbr){
	etat=nbr;
}

/**
 * Change l'etat de la case si l'etat depasse la valeur max la fonction eclater() est appelée
 * @return false si l'operation a reussie
 * @return true sinon
 */
bool Case::changerEtat(){
	etat++;
	if(etat>5)eclater();
	return true;
}

/**
 * Suprimme la bulle (etat mis a 0) et envoie l'info a la classe Algo
 * @return false si l'operation a reussie
 * @return true sinon
 */
bool Case::eclater(){
	return true;
}

/**
 * Destructeur de la class GestionEnvironnement.  
 * @return Case.etat l'etat actuel de la case(taille bulle)
 */
unsigned int Case::getEtat(){
	return etat;
}

/**
 * Destructeur de la class Case.  
 */
Case::~Case(){

}
