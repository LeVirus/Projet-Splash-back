#include <iostream>
#include "Grille.hpp"
#include "constantes.hpp"

using namespace std;

Grille *memGrille;

/**
 * Constructeur de Grille
 *	Initialise la grille (tableau 2 dimensions), 
 */
Grille::Grille(){
	memGrille=this;
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
bool Grille::appliquerChangeCase(unsigned int x, unsigned int y){
	if(largeurG<x || longueurG<y)return false;
	if(tabGrille[y][x].changerEtat())resolutionEclatement(x,y);
}

/**
 * @param lvl Indique le niveau actuel
 * Generation de la grille aleatoirement la difficulte est determine
 *  en fonction du niveau actuel
 */
void resolutionEclatement(unsigned int x, unsigned int y){
	unsigned int temps=0;
	ActionBulle* mem;
	if(y>0){
		mem=new ActionBulle;
		ActionBulle.temps=temps;
		ActionBulle.direction=HAUT;
		ActionBulle.coX=x;
		ActionBulle.coY=y-1;
		memActionBulle.push_back(mem);
	}
	if(y<6){
		mem=new ActionBulle;
		ActionBulle.temps=temps;
		ActionBulle.direction=BAS;
		ActionBulle.coX=x;
		ActionBulle.coY=y+1;
		memActionBulle.push_back(mem);
	}
	if(x<6){
		mem=new ActionBulle;
		ActionBulle.temps=temps;
		ActionBulle.direction=DROITE;
		ActionBulle.coX=x;
		ActionBulle.coY=x+1;
		memActionBulle.push_back(mem);
	}
	if(x>0){
		mem=new ActionBulle;
		ActionBulle.temps=temps;
		ActionBulle.direction=GAUCHE;
		ActionBulle.coX=x-1;
		ActionBulle.coY=y;
		memActionBulle.push_back(mem);
	}
}

/**
 * @param lvl Indique le niveau actuel
 * Generation de la grille aleatoirement la difficulte est determine
 *  en fonction du niveau actuel
 */
void Grille::genererGrille(unsigned int lvl){
	for(unsigned int j=0;j<tabGrille.size();++j)
		for(unsigned int i=0;i<tabGrille[j].size();++i){
			tabGrille[j][i].setEtat(rand()%4);//aleatoire pour le moment
		}
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
