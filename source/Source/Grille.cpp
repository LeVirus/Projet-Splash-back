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
 * Parcour de la grille et selection de la case ayant la meilleure
 * note
 * Appel de la fonction recursFind avec les coordonnées de la case
 * sélectionnée
 */
void Grille::resolv(){
	unsigned int coupRest;
	MemRes *a=NULL;
	RetourResol *rr=NULL, *rrM=NULL;
	std::vector<std::vector<Case>> *memGr=copieTabResolv();
	coupRest=memAlgo->getCoupsR();

	for(unsigned int j=0;resolTabGrille.size();++j)				
		for(unsigned int i=0;resolTabGrille[j].size();++i){
			if(resolTabGrille[i][j].getEtat()==0 || coupRest < 5-resolTabGrille[i][j].getEtat())continue;
			//si case =0 OU nombre coups restants insuffisant pour éclater case continue
			//memo=resolTabGrille[i][j].getEtat();
			//resolTabGrille[i][j].setEtat(0);
			unsigned int mem=coupRest-(5-resolTabGrille[i][j].getEtat());
			while(!appliquerChangeCase( i,  j));
			recursFind(i,j , mem);
			rrM=recursFind(a->X, a->Y,mem);
			if( rrM && rr && rr->note<rrM->note){
				std::list<MemRes*>::iterator itMem;                 
				for(itMem=rr->lstMem->begin();itMem!=rr->lstMem->end();itMem++){
					delete (*itMem);
				}
				delete rr;
				rr=rrM;
				//memo des actions	
			}
			else if(rrM && !rr){
				rr=rrM;
			}
			else if(rrM && rr && rr->note>=rrM->note ){
				std::list<MemRes*>::iterator itMem;                 
				for(itMem=rrM->lstMem->begin();itMem!=rrM->lstMem->end();itMem++){
					delete (*itMem);
				}
				delete rrM;
				//resolTabGrille[i][j].setEtat(memo);
			}

	restoreGrille(memGr);
		}
	delete memGr;

				std::list<MemRes*>::iterator itMem;                 
				//affichage bulle a eclater
				for(itMem=rr->lstMem->begin();itMem!=rrM->lstMem->end();itMem++){
cout<<"x::"<<(*itMem)->X<<"y::"<<(*itMem)->Y<<endl;
				}
}

/**
 * Fonction de recherche des bulles qui obtiendrait 
 * les meilleures notes à l'éclatement(récursive)
 * dans le cadre de la résolution 
 * @param x coordonnee grille abscisse de la case a traiter
 * @param y coordonnee grille ordonnee de la case a traiter
 * @return note : La note attribuée au coup
 */
RetourResol *Grille::recursFind(unsigned int x, unsigned int y, unsigned int coupsRestants){


	std::vector<std::vector<Case>> *memGr=NULL;
	RetourResol *rr=NULL, *rrM=NULL;
	unsigned int noteFinal=0, coupR=memAlgo->getCoupsR();
	noteFinal=coupR-coupsRestants;//calcul note
	//if(note<noteO)note=noteO;
	//return note;
	MemRes *a=NULL, *memDest=NULL;
	memGr=copieTabResolv();//memo grille actuelle
	for(unsigned int j=BAS;j<=DROITE;++j){//test des 4 directions
		a=findCase( x,  y,j );//trouver la case
		/*si case non trouvée ou coupRestant insuffisant 
		pour causer éclatement continue*/
		if( !a || coupsRestants < a->coupsN-1)continue;
		unsigned int mem=coupsRestants-(5-resolTabGrille[a->X][a->Y].getEtat());
		//causer éclatement
		while(!appliquerChangeCase( a->X,  a->Y));
		//appel récursif(apres eclatement)
		rrM=recursFind(a->X, a->Y,mem);
		//test si nouvelle note calculé est superieure a l'ancienne
		if( rrM && rr && rr->note<rrM->note){
			noteFinal=rrM->note;
			std::list<MemRes*>::iterator itMem;                 
			for(itMem=rr->lstMem->begin();itMem!=rr->lstMem->end();itMem++){
				delete (*itMem);
			}
			delete rr;
			rr=rrM;
			//memo des actions	
		}
		else if(rrM && !rr){
			rr=rrM;
		}
		else if(rrM && rr && rr->note>=rrM->note ){
			std::list<MemRes*>::iterator itMem;                 
			for(itMem=rrM->lstMem->begin();itMem!=rrM->lstMem->end();itMem++){
				delete (*itMem);
			}
			delete rrM;

		}
		restoreGrille(memGr);
	}
	memDest=new MemRes;
	memDest->X=x;
	memDest->Y=y;
	memDest->coupsN=coupR;
	//si on se trouve sur une feuille(de l'arbre de parcour)
	if(!rr){
		rr=new RetourResol;
		rr->note=noteFinal;
	}
	rr->lstMem->push_front(memDest);
	rr->note+=noteFinal;
	restoreGrille(memGr);
	delete memGr;
	return rr;
}


void Grille::restoreGrille(std::vector<std::vector<Case>> *memG){
	for(unsigned int j=0;j<tabGrille.size();++j)
		for(unsigned int i=0;i<tabGrille[j].size();++i){
			Case a=(*memG)[i][j];
			tabGrille[i][j].setEtat((*memG)[i][j].getEtat());
			cout<<"i j"<<i<<"  "<<j<<endl;
		}

}

/**
 * Fonction de copie du tableau "réel" vers le tableau de résolution
 * (dans le cadre de la résolution) 
 */
std::vector<std::vector<Case>> *Grille::copieTabResolv(){
	std::vector<std::vector<Case>> *tab=new std::vector<std::vector<Case>>;

	(*tab).resize(6);
	for(unsigned int i=0;i<resolTabGrille.size();++i)
		(*tab)[i].resize(6);
	for(unsigned int j=0;j<tabGrille.size();++j)
		for(unsigned int i=0;i<tabGrille[j].size();++i){
			(*tab)[i][j].setEtat(tabGrille[i][j].getEtat());
			cout<<"i j"<<i<<"  "<<j<<endl;
		}
	return tab;
}


/**
 * Fonction permettant de trouver la case de collision à partir des 
 * coordonnées d'éclatement(fictif) et de la direction 
 * @param x : coordonnée grille
 * @param y : coordonnée grille
 * @param direction : la direction
 * @return : structure memoCase contient les coordonnées et la valeur de la case
 */
MemRes* Grille::findCase(unsigned int x, unsigned int y, unsigned int direction){
	MemRes *a=NULL;
	switch(direction){
		case HAUT:
			//NORD
			for(unsigned int i=y;i<resolTabGrille.size();--i){
				if( resolTabGrille[x][i].getEtat() > 0 ){
					a=new MemRes;
					a->X=x;
					a->Y=i;
					a->coupsN=5-resolTabGrille[x][i].getEtat();
					return a;
				}
			}				
			return NULL;
		case BAS:
			//SUD
			for(unsigned int i=y;i<resolTabGrille.size();++i){
				if( resolTabGrille[x][i].getEtat() > 0 ){
					a=new MemRes;
					a->X=x;
					a->Y=i;
					a->coupsN=5-resolTabGrille[x][i].getEtat();
					return a;
				}
			}				
			return NULL;
		case GAUCHE:
			//OUEST
			for(unsigned int i=y;i<resolTabGrille[0].size();++i){
				if( resolTabGrille[i][y].getEtat() > 0 ){
					a=new MemRes;
					a->X=i;
					a->Y=y;
					a->coupsN=5-resolTabGrille[i][y].getEtat();
					return a;
				}
			}				
			return NULL;
		case DROITE:
			//EST
			for(unsigned int i=y;i<resolTabGrille[0].size();--i){
				if( resolTabGrille[i][y].getEtat() > 0 ){
					a=new MemRes;
					a->X=i;
					a->Y=y;
					a->coupsN=5-resolTabGrille[i][y].getEtat();
					return a;
				}
			}				
			return NULL;
		default:
			cout<<"erreur direction find Cse"<<endl;
			return NULL;
			break;
	}

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
