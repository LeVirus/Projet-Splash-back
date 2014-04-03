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

/**
 * Fonction permettant de lancer le jeu aprés avoir verifié
 * toutes les conditions necessaires au lancement( verif() )
 */
		void Base::initJeu(){
		grille.genererGrille(niveauActuel);
		niveauActuel++;
		moteur.initSphere();
		}

/**
 * Fonction permettant de lancer le jeu aprés avoir verifié
 * toutes les conditions necessaires au lancement( verif() )
 */
void Base::lancerJeu(){
	//initJeu();
	moteur.liaisonBase(this);
		grille.afficherGrille();
	algo.liaisonGrille();
		moteur.launch();
		return;
	/*unsigned int x, y;
	algo.liaisonGrille();
	grille.genererGrille(0);
	do{
		if(pointActuel==0)break;
		afficherEtatActuel();
		cout<<"x?"<<endl;
		cin>>x;
		cout<<"y?"<<endl;
		cin>>y;
		if(!grille.appliquerChangeCase(x,y)){
			cout<<"erreur entre case"<<endl;
			continue;
		}
		pointActuel--;
	}while(true);*/
}

/**
 * Fonction d'affichage des parametres globaux 
 */
void Base::afficherEtatActuel()const{
	grille.afficherGrille();
	//cout<<"pointActuel"<<pointActuel<<"   niveauActuel"<<niveauActuel<<endl;
}

/**
 * Destructeur de la classe Base.  
 */
Base::~Base(){

}
