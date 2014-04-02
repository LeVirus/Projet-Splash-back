#include "Algo.hpp"
#include "Grille.hpp"
#include "constantes.hpp"

Algo *memoAlgo;

using namespace std;

extern Grille *memGrille;

Algo::Algo(){
	memoAlgo=this;
	//memTabGrille=memGrille->getTab();
}

/**
 * @param lvl Indique le niveau actuel
 * Generation de la grille aleatoirement la difficulte est determine
 *  en fonction du niveau actuel
 */
void Algo::liaisonGrille(){
	memoG=memGrille;
	if(!memGrille)cout<<"erreur alloc"<<endl;
}

/**
 * @param lvl Indique le niveau actuel
 * Generation de la grille aleatoirement la difficulte est determine
 *  en fonction du niveau actuel
 */
void Algo::jouer(){
	unsigned int x, y;
	do{
		if(!memGrille)return;
		cout<<"x?"<<endl;
		cin>>x;
		cout<<"y?"<<endl;
		cin>>y;
		//	memGrille->appliquerClick(x,y);
	}while(true);
}

/**
 * @param lvl Indique le niveau actuel
 * Generation de la grille aleatoirement la difficulte est determine
 *  en fonction du niveau actuel
 */
void Algo::afficherList()const{
	std::list<DestinationBulle*>::const_iterator itMemBulleT;
	std::list<OrigineEclatement*>::const_iterator itMemOriginT;

	cout<<"AFFICHAGE"<<endl;

	cout<<"Destination::"<<endl<<endl;
	for(itMemBulleT=memDestinationBulle.begin();itMemBulleT!=memDestinationBulle.end();itMemBulleT++){
		cout<<(*itMemBulleT)->coX<<"<<x  y>>"<<(*itMemBulleT)->coY<<endl;
		cout<<(*itMemBulleT)->temps<<"temps  "<<endl;
	}

	cout<<"Origine::"<<endl<<endl;
	for(itMemOriginT=memOrigineEclat.begin();itMemOriginT!=memOrigineEclat.end();itMemOriginT++){
		cout<<(*itMemOriginT)->coXO<<"<<x  y>>"<<(*itMemOriginT)->coYO<<endl;
		cout<<(*itMemOriginT)->tempsO<<"temps  "<<endl;
	}
	cout<<"FIN AFFICHAGE"<<endl;
}


/**
 * @param lvl Indique le niveau actuel
 * Generation de la grille aleatoirement la difficulte est determine
 *  en fonction du niveau actuel
 */
void Algo::viderListes(){
	for(itMemOriginB=memOrigineEclat.begin();itMemOriginB!=memOrigineEclat.end();itMemOriginB++){
		delete (*itMemOriginB);
	}
	for(itMemBulleB=memDestinationBulle.begin();itMemBulleB!=memDestinationBulle.end();itMemBulleB++){
		delete (*itMemBulleB);
	}
	memDestinationBulle.clear();
	memOrigineEclat.clear();
}


/**
 * @param lvl Indique le niveau actuel
 * Generation de la grille aleatoirement la difficulte est determine
 *  en fonction du niveau actuel
 */
void Algo::resolutionEclatement(unsigned int x, unsigned int y){
	OrigineEclatement* memOrigin;
	memOrigin=new OrigineEclatement;//instancier le point d'eclatement
	memOrigin->coXO=x;//init des variables positions
	memOrigin->coYO=y;

	//si la liste "Origine" est vide "temps" est init à 0
	if(memOrigineEclat.empty())memOrigin->tempsO=0;
	//sinon "temps" est récupéré dans la variable globale
	else {
		memOrigin->tempsO=memoTempsEclat;
	}

	memOrigineEclat.push_back(memOrigin);

	trouverDestination(x,y);
	//afficherList();
	// declenchement du traitement des destinations uniquement si premier eclatement
	if( memOrigineEclat.size()==1 )appliquerDestination();
}

/**
 * @param x Indique l'absisce de iterator recherché
 * @param y Indique l'ordonnée de iterator recherché
 *	 Fonction qui trouve l'iterator qui a les coordonnées 
 */
std::list<OrigineEclatement*>::iterator Algo::findItEclat(unsigned int x, unsigned int y){
	std::list<OrigineEclatement*>::iterator itMemEclatT;
	for(itMemEclatT=memOrigineEclat.begin();itMemEclatT!=memOrigineEclat.end();itMemEclatT++){
		if( (*itMemEclatT)->coXO == x  &&  (*itMemEclatT)->coYO == y )
			return itMemEclatT;
	}
	cout<<"erreur iterator non trouve"<<endl;
	(*itMemEclatT)->coXO=1000;//indique une erreur dans l'iterator
	return itMemEclatT;
}

/**
 * @param x Indique l'abscice de l'origine
 * @param y Indique l'ordonnée de l'origine
 *	 Fonction qui trouve les destinations des "projectiles" apres l'éclatement
 */
void Algo::appliquerDestination(){
	unsigned int cmpt=0, max=0;
	if(memDestinationBulle.empty())return;
	do{
		for(itMemBulle=memDestinationBulle.begin();itMemBulle!=memDestinationBulle.end();itMemBulle++){
			if( !(*itMemBulle) ){//tmp
			}//tmp
			if((*itMemBulle)->traite)continue;
			if( max < (*itMemBulle)->temps )max=(*itMemBulle)->temps;
			//si projectile touche un bord
			if( (*itMemBulle)->coX == 100  || (*itMemBulle)->coY == 100 ){
				(*itMemBulle)->traite=true;
				continue;
			}
			// si le compteur est egal a la valeur du temps de l'élément actuel
			if( (*itMemBulle)->temps == cmpt ){
				//memo du temps de la destination (utile pour l'eventuel éclatement)
				memoTempsEclat=(*itMemBulle)->temps;

				if( memoG->getTabValue( (*itMemBulle)->coX , (*itMemBulle)->coY)
						== 0	){
corrigerDestinationBulle( (*itMemBulle) );
continue;
}
				memoG->appliquerChangeCase( (*itMemBulle)->coX , (*itMemBulle)->coY);
				(*itMemBulle)->traite=true;
			}
		}
		cmpt++;
	}while(cmpt<=max);
	return;
}

/**
 *	 Fonction qui envoie (en lecture seule) les listes d'animation
 * suite a un eclatement
 */
void Algo::corrigerDestinationBulle(DestinationBulle *a){
	switch(a->direction){
		case BAS:
	for(unsigned int i=a->coY;i<NBR_CASE_Y;i++){
		if(memoG->getTabValue(a->coX, i)>0){//si une case contient une bulle
			a->temps += i - a->coY;
		a->coY=i;
	
			break;
		}
		else if(i==NBR_CASE_Y-1){//si a->cun obsta->le rencontré
			a->temps += NBR_CASE_Y-a->coY;//temps=nbr ma-> de ca->e - pos init +1
			a->coY=100;//100 représente le bord corresponda->t en fonction de la->direction
		}
	}
			break;
		case GAUCHE:
	for(unsigned int i=a->coX;i<NBR_CASE_X;i--){
		if(memoG->getTabValue(i, a->coY)>0){//si une case contient une bulle
			a->temps+= a->coX - i;
			a->coX=i;
			break;
		}
		else if(i==0){//si aucun obstacle rencontré
			a->temps+= a->coX+1;
			a->coX=100;
			break;
		}
	}
	break;
		case HAUT:
	for(unsigned int i=a->coY;i<NBR_CASE_Y;i--){
		if(memoG->getTabValue(a->coX, i)>0){//si une case contient une bulle
			a->temps+= a->coY-i;
			a->coY=i;
			break;
		}
		else if(i==0){//si aucun obstacle rencontré
			a->temps+= a->coY+1;
			a->coY=100;
			break;
		}
	}
			break;
		case DROITE:
	for(unsigned int i=a->coX;i<NBR_CASE_X;i++){
		if(memoG->getTabValue(i, a->coY)>0){//si une case contient une bulle
			a->temps+= i-a->coX;
			a->coX=i;
			break;
		}
		else if(i==NBR_CASE_X-1){//si aucun obstacle rencontré
			a->temps+= NBR_CASE_X-a->coX+1;
			a->coX=100;
			break;
		}
			break;
	}
		default:
			cout<<"erreur direction corrigerD"<<endl;
			break;
	}
cout<<a->coX<<"correction"<<a->coY<<"temps"<<a->temps<<endl;
}

/**
 *	 Fonction qui envoie (en lecture seule) les listes d'animation
 * suite a un eclatement
 */
const	AnimList Algo::getListAnim(){
	AnimList a;
	a.memListOrigine=&memOrigineEclat;
	a.memListDestination=&memDestinationBulle;
	return a;
}


/**
 * @param x Indique l'abscice de l'origine
 * @param y Indique l'ordonnée de l'origine
 *	 Fonction qui trouve les destinations des "projectiles" apres l'éclatement
 */
void Algo::trouverDestination(unsigned int x, unsigned int y){
	DestinationBulle *tmp=new DestinationBulle;
	itMemOriginB=findItEclat(x, y);
	//trouver le temps initial du point d'eclatement
	unsigned int tempsOrigine=(*itMemOriginB)->tempsO;

	//case BAS:
	tmp->direction=BAS;
	for(unsigned int i=y;i<NBR_CASE_Y;i++){
		if(memoG->getTabValue(x, i)>0){//si une case contient une bulle
			tmp->coX=x;
			tmp->coY=i;
			tmp->temps=tempsOrigine + i - y;
			break;
		}
		else if(i==NBR_CASE_Y-1){//si aucun obstacle rencontré
			tmp->coX=x;
			tmp->coY=100;//100 représente le bord correspondant en fonction de la direction
			tmp->temps=tempsOrigine + NBR_CASE_Y-x+1;//temps=nbr max de case - pos init +1
		}
	}
	tmp->traite=false;
	memDestinationBulle.push_back(tmp);


	//case HAUT:
	tmp=new DestinationBulle;
	tmp->direction=HAUT;
	for(unsigned int i=y;i<NBR_CASE_Y;i--){
		if(memoG->getTabValue(x, i)>0){//si une case contient une bulle
			tmp->coX=x;
			tmp->coY=i;
			tmp->temps=tempsOrigine + y-i;
			break;
		}
		else if(i==0){//si aucun obstacle rencontré
			tmp->coX=x;
			tmp->coY=100;
			tmp->temps=tempsOrigine + y+1;
			break;
		}
	}
	tmp->traite=false;
	memDestinationBulle.push_back(tmp);



	//case DROITE:
	tmp=new DestinationBulle;
	tmp->direction=DROITE;
	for(unsigned int i=x;i<NBR_CASE_X;i++){
		if(memoG->getTabValue(i, y)>0){//si une case contient une bulle
			tmp->coX=i;
			tmp->coY=y;
			tmp->temps=tempsOrigine + i-x;
			break;
		}
		else if(i==NBR_CASE_X-1){//si aucun obstacle rencontré
			tmp->coX=100;
			tmp->coY=y;
			tmp->temps=tempsOrigine + NBR_CASE_X-x+1;
			break;
		}
	}
	tmp->traite=false;
	memDestinationBulle.push_back(tmp);




	//case GAUCHE:
	tmp=new DestinationBulle;
	tmp->direction=GAUCHE;
	for(unsigned int i=x;i<NBR_CASE_X;i--){
		if(memoG->getTabValue(i, y)>0){//si une case contient une bulle
			tmp->coX=i;
			tmp->coY=y;
			tmp->temps=tempsOrigine + x-i;
			break;
		}
		else if(i==0){//si aucun obstacle rencontré
			tmp->coX=100;
			tmp->coY=y;
			tmp->temps=tempsOrigine + x+1;
			break;
		}
	}
	tmp->traite=false;
	memDestinationBulle.push_back(tmp);
}

Algo::~Algo(){
	viderListes();
}
