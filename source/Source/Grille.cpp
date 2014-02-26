#include <iostream>
#include "Grille.hpp"

using namespace std;

/**
 * Constructeur de Grille
 *	Initialise la grille (tableau 2 dimensions), 
 */
Grille::Grille(){
	tabGrille.resize(6);
	for(unsigned int i=0;i<tabGrille.size();++i)
		tabGrille[i].resize(6);
	largeurG=6;
	longueurG=6;
	hauteurG=0;
}

/**
 * @param x coordonnee grille abscisse de la case a traiter
 * @param y coordonnee grille ordonnee de la case a traiter
 * Fonction qui reçois les parametres pour savoir quelle bulle
 * est a traiter
 * @return true si aucun problemes n'est repporte
 * @return false sinon
 */
bool Grille::appliquerClick(unsigned int x, unsigned int y){
	return tabGrille[y][x].changerEtat();
}

/**
 * @param lvl Indique le niveau actuel
 * Generation de la grille aleatoirement la difficulte est determine
*  en fonction du niveau actuel
 */
void Grille::genererGrille(unsigned int lvl){

}

/**
 * Affichage de la grille en console
 */
void Grille::afficherGrille(){
	for(unsigned int j=0;j<tabGrille.size();++j)
		for(unsigned int i=0;i<tabGrille[j].size();++i){
			cout<<tabGrille[j][i].getEtat();
			if(j==tabGrille[i].size()-1)cout<<endl;
		}
}

/**
 * Destructeur de la class Grille.  
 */
Grille::~Grille(){

}
