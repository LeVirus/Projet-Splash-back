#include <iostream>
#include "Base.hpp"

using namespace std;

/**
 * Constructeur de la classe Base
 * Initialisation des parametres generaux
 */
Base::Base(){
	niveauActuel=0;
}

/** //debuggage
 * Fonction d'initialisation du programme
 * init de Grille et Moteur
 */
void Base::initJeu(){
	grille.genererGrille(niveauActuel);
	moteur.initSphere();
}

/**
 * Fonction modifiant le niveau actuel
 * @param choose : determine la façon de traiter la variable
 */
void Base::setCurrentLvl(bool choose){
	if(choose)niveauActuel++;
	else niveauActuel=0;	
}

/**
 * Fonction permettant de lancer le jeu aprés avoir établie
 * les liaisons entre les objets du logiciel
 */
void Base::lancerJeu(){
	moteur.liaisonBase(this);
	grille.afficherGrille();
	algo.liaisonGrille();
	moteur.launch();
	return;
}

/**
 * Fonction d'affichage des parametres globaux 
 * (Grille)
 */
void Base::afficherEtatActuel()const{
	grille.afficherGrille();
}

/**
 * Destructeur de la classe Base.  
 */
Base::~Base(){

}
