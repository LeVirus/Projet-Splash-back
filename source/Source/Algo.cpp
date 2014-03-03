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
	if(memOrigineEclat.empty())memOrigin.tempsO=0;
	//sinon "temps" est calculé en fonction des collisions précédentes
	else{
		unsigned int cmpt=0;
		//parcour de la liste "Destination"
		for(itMemBulle=memDestinationBulle.begin();itMemBulle!=memDestinationBulle.end();itMemBulle++){//a corriger____________________________
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

	trouverDestination(x,y);
// declenchement du traitement des destinations uniquement si premier eclatement
	if( memOrigineEclat.size==1 )appliquerDestination();
}

/**
 * @param x Indique l'abscice de l'origine
 * @param x Indique l'ordonnée de l'origine
 *	 Fonction qui trouve les destinations des "projectiles" apres l'éclatement
 */
void Algo::appliquerDestination(){
	unsigned int cmpt=0, max=0;
	if(memDestinationBulle.empty())return;
	//trouver le temps max dans la liste
	for(itMemBulle=memDestinationBulle.begin();itMemBulle!=memDestinationBulle.end();itMemBulle++){
		if(max<(itMemBulle*)->temps)max=(itMemBulle*)->temps;
	}
	do{
		for(itMemBulle=memDestinationBulle.begin();itMemBulle!=memDestinationBulle.end();itMemBulle++){
			if((itMemBulle*)->traite)continue;
			if( (itMemBulle*)->temps == cmpt ){
				memoG->appliquerChangeCase( (itMemBulle*)->coX , (itMemBulle*)->coY);
				(itMemBulle*)->traite=true;
			}
		}
		cmpt++;
	}while(cmpt<=max);

}

/**
 * @param x Indique l'abscice de l'origine
 * @param x Indique l'ordonnée de l'origine
 *	 Fonction qui trouve les destinations des "projectiles" apres l'éclatement
 */
void Algo::trouverDestination(unsigned int x, unsigned int y){
	DestinationBulle *tmp=new DestinationBulle;
	//case BAS:
	tmp->direction=BAS;
	for(unsigned int i=y;i<NBR_CASE_Y;i++){
		if(memTabGrille[x][i]->getEtat()>0){//si une case contient une bulle
			tmp->coX=x;
			tmp->coY=i;
			tmp->temps=i-y;
			break;
		}
		else if(i==NBR_CASE_Y-1){//si aucun obstacle rencontré
			tmp->coX=x;
			tmp->coY=100;//100 représente le bord correspondant en fonction de la direction
			tmp->temps=NBR_CASE_Y-i+1;//temps=nbr max de case - pos init +1
		}
	}
	tmp->traite=false;
	memDestinationBulle.push_back(tmp);
	//break;
	//case HAUT:
	tmp=new DestinationBulle;
	tmp->direction=HAUT;
	for(unsigned int i=y;i>=0;i--){
		if(memTabGrille[x][i]->getEtat()>0){
			tmp->coX=x;
			tmp->coY=i;
			tmp->temps=y-i;
			break;
		}
		else if(i==NBR_CASE_Y-1){//si aucun obstacle rencontré
			tmp->coX=x;
			tmp->coY=100;
			tmp->temps=y+1;
		}
	}
	tmp->traite=false;
	memDestinationBulle.push_back(tmp);
	//		break;
	//case DROITE:
	tmp=new DestinationBulle;
	tmp->direction=DROITE;
	for(unsigned int i=x;i<NBR_CASE_X;i++){
		if(memTabGrille[i][y]->getEtat()>0){
			tmp->coX=i;
			tmp->coY=y;
			tmp->temps=i-x;
			break;
		}
		else if(i==NBR_CASE_Y-1){//si aucun obstacle rencontré
			tmp->coX=100;
			tmp->coY=y;
			tmp->temps=NBR_CASE_X-x+1;
		}
	}
	tmp->traite=false;
	memDestinationBulle.push_back(tmp);
	//break;
	//case GAUCHE:
	tmp=new DestinationBulle;
	tmp->direction=GAUCHE;
	for(unsigned int i=x;i>=0;i--){
		if(memTabGrille[x][i]->getEtat()>0){
			tmp->coX=i;
			tmp->coY=y;
			tmp->temps=y-i;
			break;
		}
		else if(i==NBR_CASE_Y-1){//si aucun obstacle rencontré
			tmp->coX=100;
			tmp->coY=y;
			tmp->temps=x+1;
		}
	}
	tmp->traite=false;
	memDestinationBulle.push_back(tmp);
}

Algo::~Algo(){

}
