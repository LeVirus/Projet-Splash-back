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
	unsigned int noteCurrent=0, noteFinal=0, memX, memY,coupRest, memo;
copieTabResolv();
	for(unsigned int j=0;resolTabGrille.size();++j)				
		for(unsigned int i=0;resolTabGrille[j].size();++i){
			if(resolTabGrille[i][j].getEtat()==0 || coupRest < 5-resolTabGrille[i][j].getEtat())continue;
			//si case =0 OU nombre coups restants insuffisant pour éclater case continue
			memo=resolTabGrille[i][j].getEtat();
			resolTabGrille[i][j].setEtat(0);
			recursFind(i,j , coupRest-(5-resolTabGrille[i][j].getEtat()));
			resolTabGrille[i][j].setEtat(memo);
}
}

	/**
	 * Fonction de recherche des bulles les plus proches(récursive)
	 * dans le cadre de la résolution 
	 * @param x coordonnee grille abscisse de la case a traiter
	 * @param y coordonnee grille ordonnee de la case a traiter
	 * @return note : La note attribuée au coup
	 */
	unsigned int Grille::recursFind(unsigned int x, unsigned int y, unsigned int coupsRestants){
		unsigned int note=0, noteFinal=0, memo;
		/*	if(note<noteO)note=noteO;
				return note;*/
		MemRes *a=NULL;
		for(unsigned int j=BAS;j<=DROITE;++j){
			a=findCase( x,  y,j );
			if( coupRest < a->coupsN-1)continue;
			memo=resolTabGrille[i][j].getEtat();
			resolTabGrille[i][j].setEtat(0);
			note=attribuerNote(a->X,a->Y);

			resolTabGrille[i][j].setEtat(memo);
			if(noteFinal<note){
				noteFinal=note;
				memX=i;
				memY=j;
			}
		}
	}


/**
 * Fonction de copie du yableau "réel" vers le tableau de résolution
 * (dans le cadre de la résolution) 
 */
void Grille::copieTabResolv(){
	for(unsigned int i=0;i<resolTabGrille.size();++i)
		resolTabGrille[i].resize(6);
	for(unsigned int j=0;j<tabGrille.size();++j)
		for(unsigned int i=0;i<tabGrille[j].size();++i){
			resolTabGrille[i][j].setEtat(tabGrille[i][j].getEtat());
		}
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
				break;
		}

	}


	/**
	 * Fonction de détermination de la note suite à l'éclatement(théorique)
	 * @param x : coordonnée grille
	 * @param y : coordonnée grille
	 * @return note: la note associée à l'éclatement
	 */
	unsigned int Grille::attribuerNote(unsigned int x, unsigned int y){
		unsigned int finall=0;
		//f( coupsRestants - ( 4-tabGrille[x][i] ) > 0 )
		//représente le nombre de coups a réaliser sur la 
		//case(en plus de la bulle mouvante)pour la faire éclater
		//noteN=recursFind( x,  i, coupsRestants - ( 4-tabGrille[x][i] ) );
		MemRes *memC;
		//NORD
		for(unsigned int j=BAS;j<=DROITE;++j){
			memC=findCase(x, y,  j);
			if(memC){
				finall+=5-memC->coupsN;//add valeur case touchée
				if(memC->coupsN==1){
					finall+=attribuerNote( memC->X, memC->Y);//si eclatement ajout des points obtenus avec le nouvel eclatement
				}
			}
		}
		//SUD
		/*memC=findCase(x, y,  BAS);
			if(memC){
			finall+=5-memC->coupsN;//add valeur case touchée
			if(memC->getEtat()==4){
			finall+=attribuerNote( memC->X, memC->Y);//si eclatement ajout des points obtenus avec le nouvel eclatement
			}
			}

		//EST
		memC=findCase(x, y,  DROITE);
		if(memC){
		finall+=5-memC->coupsN;//add valeur case touchée
		if(memC->getEtat()==4){
		finall+=attribuerNote( memC->X, memC->Y);//si eclatement ajout des points obtenus avec le nouvel eclatement
		}
		}

		//OUEST
		memC=findCase(x, y,  GAUCHE);
		if(memC){
		finall+=5-memC->coupsN;//add valeur case touchée
		if(memC->getEtat()==4){
		finall+=attribuerNote( memC->X, memC->Y);//si eclatement ajout des points obtenus avec le nouvel eclatement
		}
		}*/
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
