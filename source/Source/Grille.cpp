#include <iostream>
#include "Grille.hpp"
#include "Algo.hpp"
#include "constantes.hpp"

using namespace std;

extern Algo *memoAlgo;
Grille *memGrille;

/**
 * Constructeur de Grille
 *	Initialise la grille (tableau 2 dimensions), 
 */
Grille::Grille(){
	if(memoAlgo)memAlgo=memoAlgo;
	else cout<<"erreur alloc memAlgo"<<endl;
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
 * @return true si eclatement
 * @return false sinon
 */
bool Grille::appliquerChangeCase(unsigned int x, unsigned int y){
	if(largeurG<x || longueurG<y){
		cout<<"erreur select"<<endl;
			return false;
}
//si eclatement
	if(tabGrille[x][y].changerEtat()){
		memAlgo->resolutionEclatement(x,y);
	return true;
	}
			return false;
}

/**
 * @param lvl Indique le niveau actuel
 * Generation de la grille aleatoirement la difficulte est determine
 *  en fonction du niveau actuel
 */
unsigned int Grille::getTabValue(unsigned int x, unsigned int y)const{
	if(x>=largeurG || y>=longueurG)return 1000;//si erreur
	return tabGrille[x][y].getEtat();
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
 * Renvoie une référence constante du tableau représentatif du jeu
 */
const std::vector<std::vector<Case>> *Grille::getTab()const{
	return &tabGrille;
}

/**
 * Affichage de la grille en console
 */
void Grille::afficherGrille()const{
	cout<<"AFFICHAGE"<<endl;
	for(unsigned int j=0;j<tabGrille.size();++j)
		for(unsigned int i=0;i<tabGrille[j].size();++i){
			cout<<tabGrille[i][j].getEtat();
			if(i==tabGrille[j].size()-1)cout<<endl;
		}
	cout<<"FIN AFFICHAGE"<<endl;
}

const std::vector<std::vector<Case>> &Grille::getTabGrille()const{
	return tabGrille;
}

/**
 * Destructeur de la class Grille.  
 */
Grille::~Grille(){

}
