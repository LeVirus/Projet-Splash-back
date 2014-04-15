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
	srand(time(NULL));
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
 * Fonction qui traite la bulle dont les coordonnées sont envoyées en paramêtres
 * @param x coordonnee grille abscisse de la case a traiter
 * @param y coordonnee grille ordonnee de la case a traiter
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
 * Fonction retournant l'état de la case envoyée en paramêtre
 * @param x coordonnee grille abscisse de la case a traiter
 * @param y coordonnee grille ordonnee de la case a traiter
 * @return valeurTableau : L'état de la case correspondante
 */
unsigned int Grille::getTabValue(unsigned int x, unsigned int y)const{
	if(x>=largeurG || y>=longueurG)return 1000;//si erreur
	return tabGrille[x][y].getEtat();
}

/**
 * Fonction de resolution de la grille
 */
void Grille::resolv(){
	unsigned int search=4, cmptX, cmptY, coupRest;
	do{
		for(unsigned int j=0;tabGrille.size();++j)				
			for(unsigned int i=0;tabGrille[j].size();++i){
				switch(tabGrille[i][j]){
					case 0:
						continue;
						break;
					case 1:
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
					default:
						cout<<"erreur resolv"<<endl;
						break;
				}
			}				
	}while();	
}


/**
 * Fonction de recherche des bulles les plus proches(récursive)
 * dans le cadre de la résolution 
 * @param x coordonnee grille abscisse de la case a traiter
 * @param y coordonnee grille ordonnee de la case a traiter
 * @return note : La note attribuée au coup
 */
unsigned int Grille::recursFind(unsigned int x, unsigned int y, unsigned int coupsRestants){
unsigned int note=0, nombreEclatement=0, noteN, noteE, noteS, noteO;
	//NORD
	for(unsigned int i=y;i<tabGrille.size();--i){
		if( tabGrille[x][i] > 0 ){
			if( coupsRestants - ( 4-tabGrille[x][i] ) > 0 )
				//représente le nombre de coups a réaliser sur la 
				//case(en plus de la bulle mouvante)pour la faire éclater
				noteN=recursFind( x,  i, coupsRestants - ( 4-tabGrille[x][i] ) );
			if(tabGrille[x][i]==4){
				nombreEclatement++;
				note+=noteS;
			}
			break;
		}
	}				
	note=noteN;
	//SUD
	for(unsigned int i=y;i<tabGrille.size();++i){
		if( tabGrille[x][i] > 0){
			if( coupsRestants - ( 4-tabGrille[x][i] ) > 0 )
				noteS=recursFind( x,  i, coupsRestants - ( 4-tabGrille[x][i] ) );
			if(tabGrille[x][i]==4){
				nombreEclatement++;
				note+=noteS;
			}
			break;
		}

	}				
	if(note<noteS)note=noteS;
	//EST
	for(unsigned int i=y;i<tabGrille[0].size();--i){
		if( tabGrille[i][y] > 0 ){
			if( coupsRestants - ( 4-tabGrille[i][y] ) > 0 )
				noteE=recursFind( i,  y, coupsRestants - ( 4-tabGrille[i][y] ) );
			if(tabGrille[i][y]==4){
				nombreEclatement++;
				note+=noteE;
			}
			break;
		}

	}				
	if(note<noteE)note=noteE;
	//OUEST
	for(unsigned int i=y;i<tabGrille[0].size();++i){
		if( tabGrille[i][y] > 0 ){
			if( coupsRestants - ( 4-tabGrille[i][y] ) > 0 )
				noteO=recursFind( i,  y, coupsRestants - ( 4-tabGrille[i][y] ) );
			if(tabGrille[i][y]==4){
				nombreEclatement++;
				note+=noteO;
			}
			break;
		}

	}				
	if(note<noteO)note=noteO;
	return note;
}

/**
 * Generation de la grille aleatoirement la difficulte est determine
 *  en fonction du niveau actuel(paramètre lvl)
 * @param lvl : niveau actuel
 */
void Grille::genererGrille(unsigned int lvl){
	unsigned int nbrB4, nbrB3, nbrB2, nbrB1, nbrB0=36,finall;
	bool correct=false;
	if(lvl<4){
		nbrB4=5+rand()%2;
		nbrB0-=nbrB4;
		nbrB3=9+rand()%2;
		nbrB0-=nbrB3;
		nbrB2=9+rand()%2;
		nbrB0-=nbrB2;
		nbrB1=5+rand()%2;
		nbrB0-=nbrB1;
	}
	else if(lvl<7){
		nbrB4=4+rand()%2;
		nbrB0-=nbrB4;
		nbrB3=7+rand()%2;
		nbrB0-=nbrB3;
		nbrB2=10+rand()%2;
		nbrB0-=nbrB2;
		nbrB1=7+rand()%2;
		nbrB0-=nbrB1;
	}
	else if(lvl<10){
		nbrB4=3+rand()%2;
		nbrB0-=nbrB4;
		nbrB3=5+rand()%2;
		nbrB0-=nbrB3;
		nbrB2=10+rand()%2;
		nbrB0-=nbrB2;
		nbrB1=10+rand()%2;
		nbrB0-=nbrB1;
	}
	else{
		nbrB4=2+rand()%2;
		nbrB0-=nbrB4;
		nbrB3=3+rand()%2;
		nbrB0-=nbrB3;
		nbrB2=11+rand()%2;
		nbrB0-=nbrB2;
		nbrB1=12+rand()%2;
		nbrB0-=nbrB1;
	}
	for(unsigned int j=0;j<tabGrille.size();++j)
		for(unsigned int i=0;i<tabGrille[j].size();++i){
			int tmp=rand()%5;
			do{
				correct=false;
				switch(tmp){
					case 0:
						if(nbrB0==0)correct=true;
						break;
					case 1:
						if(nbrB1==0)correct=true;
						break;
					case 2:
						if(nbrB2==0)correct=true;
						break;
					case 3:
						if(nbrB3==0)correct=true;
						break;
					case 4:
						if(nbrB4==0)correct=true;
						break;
					default:
						cout<<"erreur rand"<<endl;
						break;
				}
				if(!correct)finall=tmp;
				else{
					tmp++;
					if(tmp>4)tmp=0;
				}

			}while(correct);
			tabGrille[i][j].setEtat(finall);
		}
}

/**
 * Renvoie une référence constante du tableau représentatif du jeu
 * @return Tableau<Case*> : ref const du tableau stocké
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
