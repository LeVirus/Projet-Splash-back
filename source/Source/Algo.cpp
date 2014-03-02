#include <iostream>
#include "Algo.hpp"
#include "Grille.hpp"
#include "constantes.hpp"

using namespace std;

extern Grille *memGrille;

Algo::Algo(){
	memoG=memGrille;
	if(!memGrille)cerr<<"erreur alloc"<<endl;
	memTabGrille=memGrille->getTab();
}

void Algo::jouer(){
	unsigned int x, y;
	do{
		if(!memGrille)return;
		cout<<"x?"<<endl;
		cin>>x;
		cout<<"y?"<<endl;
		cin>>y;
		memGrille->appliquerClick(x,y);
	}while(true);
}

/**
 * @param lvl Indique le niveau actuel
 * Generation de la grille aleatoirement la difficulte est determine
 *  en fonction du niveau actuel
 */
void Algo::resolutionEclatement(unsigned int x, unsigned int y){
	DestinationBulle* memMove;
	OrigineEclatement* memOrigin;
	memOrigin=new memOrigin;//instancier le point d'eclatement
	memOrigin.coXO=x;//init des variables positions
	memOrigin.coYO=y;

	//si la liste "Origine" est vide "temps" est init à 0
	if(memOrigineEclat.size()==0)memOrigin.tempsO=0;
	//sinon "temps" est calculé en fonction des collisions précédentes
	else{
		unsigned int cmpt=0;
		//parcour de la liste "Destination"
		for(itMemBulle=memDestinationBulle.begin();itMemBulle!=memDestinationBulle.end();itMemBulle++){
			/* Recherche des coordonnées X et Y correspondantes
				 dans la liste des Destinations */
			if(memOrigin->coXO==(itMemBulle*)->coX  && 
					memOrigin->coYO==(itMemBulle*)->coY){
				//attribution du temps
				memOrigin->tempsO=(itMemBulle*)->temps;
			}
		}
	}

	memOrigineEclat.push_back(memOrigin);//premier eclatement
	if(y>0){
		memMove=new DestinationBulle;
		DestinationBulle.temps=temps;
		DestinationBulle.direction=HAUT;
		DestinationBulle.coX=x;
		DestinationBulle.coY=y-1;
		memDestinationBulle.push_back(memMove);
	}
	if(y<6){
		memMove=new DestinationBulle;
		DestinationBulle.temps=temps;
		DestinationBulle.direction=BAS;
		DestinationBulle.coX=x;
		DestinationBulle.coY=y+1;
		memDestinationBulle.push_back(memMove);
	}
	if(x<6){
		memMove=new DestinationBulle;
		DestinationBulle.temps=temps;
		DestinationBulle.direction=DROITE;
		DestinationBulle.coX=x;
		DestinationBulle.coY=x+1;
		memDestinationBulle.push_back(memMove);
	}
	if(x>0){
		memMove=new DestinationBulle;
		DestinationBulle.temps=temps;
		DestinationBulle.direction=GAUCHE;
		DestinationBulle.coX=x-1;
		DestinationBulle.coY=y;
		memDestinationBulle.push_back(memMove);
	}
}

DestinationBulle *Algo::trouverDestination(unsigned int x, unsigned int y, unsigned int direction){
	DestinationBulle *tmp=new DestinationBulle;
	tmp->direction=direction;
	switch(destination){
		case BAS:
			for(unsigned int i=y;i<NBR_CASE_Y;i++)
				if(memTabGrille[x][i]->getEtat()>0){
					tmp->coX=x;
					tmp->coY=i;
					tmp->temps=i-y;
					memDestinationBulle.push_back(tmp);
					return;
				}
			break;
		case HAUT:
			for(unsigned int i=y;i>=0;i--)
				if(memTabGrille[x][i]->getEtat()>0){
					tmp->coX=x;
					tmp->coY=i;
					tmp->temps=y-i;
					memDestinationBulle.push_back(tmp);
					return;
				}
			break;
		case DROITE:
			for(unsigned int i=x;i<NBR_CASE_X;i++)
				if(memTabGrille[i][y]->getEtat()>0){
					tmp->coX=i;
					tmp->coY=y;
					tmp->temps=i-x;
					memDestinationBulle.push_back(tmp);
					return;
				}
			break;
		case GAUCHE:
			for(unsigned int i=x;i>=0;i--)
				if(memTabGrille[x][i]->getEtat()>0){
					tmp->coX=i;
					tmp->coY=y;
					tmp->temps=y-i;
					memDestinationBulle.push_back(tmp);
					return;
				}
			break;
		default:
			cout<<"erreur direction"<<endl;
			return;
	};

//si aucun obstacles rencontrés
	switch(direction){
		case BAS:
			tmp->coX=x;
			tmp->coY=100;
			tmp->temps=NBR_CASE_Y-i+1;
			memDestinationBulle.push_back(tmp);
			return;
			break;
		case HAUT:
			tmp->coX=x;
			tmp->coY=100;
			tmp->temps=y+1;
			memDestinationBulle.push_back(tmp);
			return;
			break;
		case GAUCHE:
			tmp->coX=100;
			tmp->coY=y;
			tmp->temps=x+1;
			memDestinationBulle.push_back(tmp);
			return;
			break;
		case DROITE:
			tmp->coX=100;
			tmp->coY=y;
			tmp->temps=NBR_CASE_X-x+1;
			memDestinationBulle.push_back(tmp);
			return;
			break;
		default:
			break;
	};
}

Algo::~Algo(){

}
