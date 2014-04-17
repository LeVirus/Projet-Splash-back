#include <iostream>
#include <vector>
#include "Moteur.hpp"
#include "Base.hpp"
#include "Case.hpp"
#include "Grille.hpp"
#include "constantes.hpp"

using namespace std;

extern Grille *memGrille;
extern Algo *memoAlgo;

/**
 * Constructeur de la classe Moteur.
 * Initialisation des variables de base,
 * du tableau(vector) de stockage des bulles
 * et	appel de la fonction "initMoteur()"
 */
Moteur::Moteur(){
	quit=false;
	animEnCours=false;
	actionEnCours=false;
	vectSphere.resize(NBR_CASE_X);
	for(unsigned int i=0;i<NBR_CASE_Y;++i)
		vectSphere[i].resize(NBR_CASE_Y);
	initMoteur();
}

/**
 * Initialisation des objets necessaires au moteur
 * Module créés : GUI, SceneManager, Caméra 
 * Assignation des touches(clavier)
 * Creation de la grille (cube et bulle)
 * @return true : si tous les objets sont créés avec succés
 * @return false : si un probleme est survenu
 */
bool Moteur::initMoteur(){

	device = irr::createDevice (
			irr::video::EDT_OPENGL,
			irr::core::dimension2d<irr::u32>(800,600),
			32,
			false,
			true,
			false,
			&receiver);

	driver = device->getVideoDriver();
	sceneManager = device->getSceneManager ();
	device->getCursorControl ()-> setVisible (true);


	//recup de la gui dans le moteur
	gui = device->getGUIEnvironment();

	//BUUUGGG

	font = gui->getFont("Ressources/Roboto-Medium.ttf");
	if(!font)cerr<<"erreur chargement"<<endl;
	//font->setKerningHeight	(	20	);//modif la hauteur	
	//font->setKerningWidth	(	20	);	//modif la longueur	

	//BUUUGGG

	irr::scene::IMeshSceneNode* cube;         // pointeur vers le node
	irr::f32 x=0.0f ,y=0.0f,z=0.0f;
	for(unsigned int i=0;i < NBR_CASE_X*NBR_CASE_Y;++i){
		cube=sceneManager->addCubeSceneNode(        // la creation du cube
				10.0f,                             // cote de 10 unites
				0,                                 // parent = racine
				-1,                                // pas d'ID
				irr::core::vector3df(              // le vecteur de position
					x,                          // origine en X
					y,                          // origine en Y
					z));                       // +20 unites en Z
		Bulle *a=new Bulle;
		cube->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
		irr::scene::ITriangleSelector *triangleCol=
			sceneManager->createOctreeTriangleSelector(
					cube->getMesh(), cube, 128);

		cube->setTriangleSelector(triangleCol);
		triangleCol->drop();
		a->noeudCase=cube;
		vectSphere[i%NBR_CASE_X][i/NBR_CASE_X]=a;
		//memo de la case dans le tableau
		x+=10.0f;
		if(x>=60.0f){
			x=0.0f;
			y-=10.0f;
		}
	}


	// pointeur vers le node
	irr::SKeyMap keyMap[5];                    // re-assigne les commandes
	keyMap[0].Action = irr::EKA_MOVE_FORWARD;  // avancer
	keyMap[0].KeyCode = irr::KEY_KEY_Z;        // w
	keyMap[1].Action = irr::EKA_MOVE_BACKWARD; // reculer
	keyMap[1].KeyCode = irr::KEY_KEY_S;        // s
	keyMap[2].Action = irr::EKA_STRAFE_LEFT;   // a gauche
	keyMap[2].KeyCode = irr::KEY_KEY_Q;        // a
	keyMap[3].Action = irr::EKA_STRAFE_RIGHT;  // a droite
	keyMap[3].KeyCode = irr::KEY_KEY_D;        // d
	camera = sceneManager->addCameraSceneNodeFPS(       
			// ajout de la camera FPS
			0,                                     // pas de noeud parent
			100.0f,                                // vitesse de rotation
			0.1f,                                  // vitesse de deplacement
			-1,                                    // pas de numero d'ID
			keyMap,                                // on change la keymap
			5);                                    // avec une taille de 5


	return true;
}

/**
 * Fonction qui mémorise l'adresse de l'objet Base
 * Si le pointeur est NULL un message d'erreur est affiché
 * @param a : Le pointeur de l'objet Base
 */
void Moteur::liaisonBase(Base *a){
	if(!a)cout<<"erreur liaison Base Moteur cpp"<<endl;
	memBase=a;
}

/**
 * Procedure d'initialisation des spheres a l'affichage(Irrlicht)
 * Création des différents noeuds spheres à l'endroit requis 
 * Lis les donnees à partir de la classe Grille (le tableau qui stocke 
 * l'état des bulles est récupéré par référence) 
 */
void Moteur::initSphere(){
	irr::scene::IMeshSceneNode *sphere;         // pointeur vers le node
	irr::f32 x=0.0f ,y=0.0f,z=0.0f, tailleSphere;
	unsigned int taille;
	std::vector<std::vector<Case>> tmp=memGrille->getTabGrille();
	for(unsigned int j=0;j<tmp.size();j++)
		for(unsigned int i=0;i<tmp[j].size();i++){
			taille=tmp[i][j].getEtat();
			switch(taille){
				case 0:
					vectSphere[i][j]->noeudSphere=NULL;
					x+=10.0f;
					if(x>=60.0f){
						x=0.0f;
						y-=10.0f;
					}
					vectSphere[i][j]->taille=0;
					continue;
					break;
				case 1:
					tailleSphere=2.0f;
					vectSphere[i][j]->taille=1;
					break;
				case 2:
					tailleSphere=3.0f;
					vectSphere[i][j]->taille=2;
					break;
				case 3:
					tailleSphere=4.0f;
					vectSphere[i][j]->taille=3;
					break;
				case 4:
					tailleSphere=5.0f;
					vectSphere[i][j]->taille=4;
					break;
				default:
					cerr<<"erreur taille non valide initSphere"<<endl;
					break;
			}
			sphere=sceneManager->addSphereSceneNode	(	


					tailleSphere,  //taille rayon f32
					16, //nombre de polycount?? s32
					0,// noeud parent
					-1, //id s32
					//		const core::vector3df &		position = 
					irr::core::vector3df(x, y, z),
					//			const core::vector3df &		rotation = 
					irr::core::vector3df(0, 0, 0),
					//				const core::vector3df &		scale = 
					irr::core::vector3df(1.0f, 1.0f, 1.0f) 
					);	
			//sceneManager->getMeshManipulator()->makePlanarTextureMapping(sphere->getMesh(), 0.04f);

			//sphere->setMaterialTexture( 0, driver->getTexture("Ressources/blackbuck.bmp") );
			vectSphere[i][j]->noeudSphere=sphere;

			x+=10.0f;
			if(x>=60.0f){
				x=0.0f;
				y-=10.0f;
			}
		}

}

/**
 * Boucle générale du moteur physique
 * Initialisation de la détection des evenements souris
 * Gestion des mises à jour et des animations des bulles(communication avec 
 * les classes Grille et Algo)
 * Gestion des évenements souris
 * A la fin de la fonction le device est supprimé 
 * @return false : si la fonction a fermée suite à un problème
 * @return true : si la fonction a fermée aprés avoir reçu un signal d'arret(alt+f4)
 */
bool Moteur::launch(){
	irr::core::vector3df outCollisionPoint;
	irr::core::triangle3df outTriangle;
	irr::core::line3df ray; 
	irr::scene::ISceneCollisionManager* collisionManager = 
		sceneManager->getSceneCollisionManager();
	std::list<OrigineEclatement*>::iterator itOrigine;
	texte = gui->addStaticText(L" Niveau::\n"
			" 'Coups Restants::",
			irr::core::rect<irr::s32>(100,20,300,100), true, true, 0, -1, true);
	//texte->setOverrideFont(font);
	//pour rect:: 2 premiers parametre le coin sup gauche
	//2 derniers parametres coin inf droit


	do{
		coupRestant=10;
		memBase->initJeu();
		while(device->run()) {
			if( !receiver.leftButtonIsPressed() )actionEnCours=false;
			//attendre que le bouton soit relacher pour reinitialiser
			//la variable




			//Animations ________________________________________________
			if(animEnCours  ){
				//comparaison du temps actuel convertis en secondes avec le temps
				//du point Origine de l'eclatement
				//tant qu'un eclatement se produit au temps T
				while(true){
					if( itOrigine!=memListAnim.memListOrigine->end() 
							&&	(*itOrigine)->tempsO*1000<=iterationAct ){
						changerTailleSphere( (*itOrigine)->coXO, 
								(*itOrigine)->coYO , true);




						creerBulleMouvante((*itOrigine)->coXO, (*itOrigine)->coYO );


						itOrigine++;
						//pusher les 4 spheres mouvantes
						//creer une nouvelle liste
					}
					else break;
				}
				actionBullesMouvantes();
				if( lstSphereMouvante.empty() && 
						itOrigine==memListAnim.memListOrigine->end() ){

					animEnCours=false;
					if(verifTabVide()){
						cout<<"niveau termine"<<endl;
						memBase->setCurrentLvl(true);
						coupRestant++;
						break;
					}

					coupRestant+=(memListAnim.memListOrigine->size()-1)/2;
					cout<<"coupRestant"<<coupRestant<<endl;
					memoAlgo->viderListes();
				}
				iterationAct+=200;

			}

			//Animations ________________________________________________




			//action souris________________________________________________

			if(!actionEnCours  && !animEnCours  ){
				if(coupRestant==0){
					cout<<"jeu finis"<<endl;
					memBase->setCurrentLvl(false);
					break;//sortir de la boucle principalle
				}
				if( receiver.rightButtonIsPressed() ){
					quit=true;
					break;
				}
				if( receiver.leftButtonIsPressed() ){
					actionEnCours=true;
					// Crée un rayon partant du curseur de la souris.
					ray = collisionManager->getRayFromScreenCoordinates(
							device->getCursorControl()->getPosition()
							, camera);

					irr::scene::ISceneNode* node = 
						collisionManager->getSceneNodeAndCollisionPointFromRay(
								ray, outCollisionPoint, outTriangle);

					//si !node aucune collision avec un noeud
					if(node){
						coupRestant--;
						cout<<"coupRestant"<<coupRestant<<endl;
						for(unsigned int i=0;
								i<vectSphere[0].size()*vectSphere.size();i++){
							if(vectSphere[i%NBR_CASE_X][i/NBR_CASE_X]->
									noeudCase==node ){
								//identification du noeud
								memGrille->appliquerChangeCase(
										i%NBR_CASE_X, i/NBR_CASE_X);
								//modification de la valeur dans Grille

								//si eclatement_________________________________________
								if( memGrille->getTabValue( 
											i%NBR_CASE_X, i/NBR_CASE_X )
										== 0 ){
									memListAnim=memoAlgo->getListAnim();
									itOrigine=memListAnim.memListOrigine->begin();
									itDestination=memListAnim.memListDestination->begin();
									animEnCours=true;
									iterationAct=0;
								}

								//si aucun eclatement____________________________________
								else{
									//cerr<<i%NBR_CASE_X<<" detected"<<i/NBR_CASE_X<<endl;
									changerTailleSphere( i%NBR_CASE_X, i/NBR_CASE_X,true );
								}

								break;
							}
						}
					}
				}
			}

			//action souris________________________________________________







			driver->beginScene (true, true,
					irr::video::SColor(255,255,255,255));
			sceneManager->drawAll ();
			gui->drawAll();
			driver->endScene ();


		}
		viderTabBulles();
	}while(!quit);

	//cerr<<"ss"<<endl;
	device->drop (); 
	return true;
}


/**
 * Fonction verifiant si le tableau de bulle est vide
 * @return true : si tableau vide
 * @return false : sinon
 */
bool Moteur::verifTabVide(){
	for(unsigned int j=0;j<vectSphere.size();j++)
		for(unsigned int i=0;i<vectSphere[j].size();i++){
			if(vectSphere[i][j]->taille!=0){
				return false;
			}
		}
	return true;
}

/**
 * Fonction permettant de changer graphiquement la taille d'une sphere
 * le booleen détermine si la taille de la bulle doit être
 * directement incrémentée(false) ou mise a jour à partir de la classe Grille(true)
 * @param x : l'abscisse de la case à traiter
 * @param y : l'ordonnée de la case à traiter
 * @param lectAlg : mode de traitement
 */
void Moteur::changerTailleSphere(unsigned int x, unsigned int y, bool lectAlg){
	unsigned int tailleSphere;
	//init valeur a 0
	//si lectAlgo lecture de la valeur dans Grille
	if(lectAlg){
		vectSphere[x][y]->taille=memGrille->getTabValue(x, y);
	}
	//sinon incrementation de la valeur actuelle (dans Moteur)
	else {
		if(vectSphere[x][y]->taille==0)return;
		vectSphere[x][y]->taille++;
		if(vectSphere[x][y]->taille>4)vectSphere[x][y]->taille=0;
	}
	//si sphere non instanciée
	switch(vectSphere[x][y]->taille){ 
		case 0:
			tailleSphere=0.0f;
			break;
		case 1:
			tailleSphere=2.0f;
			break;
		case 2:
			tailleSphere=3.0f;
			break;
		case 3:
			tailleSphere=4.0f;
			break;
		case 4:
			tailleSphere=5.0f;
			break;
		case 1000:
			return;
			break;
		default:
			cerr<<"erreur taille non valide initSphere"<<
				memGrille->getTabValue(x, y)<<endl;
			return;
			break;
	}
	//supr du noeud bulle
	if(vectSphere[x][y]->noeudSphere){
		vectSphere[x][y]->noeudSphere->remove(); 
		vectSphere[x][y]->noeudSphere=NULL;
	}
	//si taille == 0 le noeud n'est pas recréé
	if(tailleSphere==0.0f)return;
	vectSphere[x][y]->noeudSphere = sceneManager->addSphereSceneNode	(	


			tailleSphere,  //taille rayon f32
			16, //nombre de polycount?? s32
			0,// noeud parent
			-1, //id s32
			//		const core::vector3df &		position = 
			vectSphere[x][y]->noeudCase->getPosition(),
			//			const core::vector3df &		rotation = 
			irr::core::vector3df(0, 0, 0),
			//				const core::vector3df &		scale = 
			irr::core::vector3df(1.0f, 1.0f, 1.0f) 
			);	

}

/**
 * Fonction permettant de supprimer les noeuds spheres 
 * contenus dans le tableau
 */
void Moteur::viderTabBulles(){
	for(unsigned int j=0;j<vectSphere.size();j++)
		for(unsigned int i=0;i<vectSphere[j].size();i++){
			if(vectSphere[i][j]->noeudSphere){
				vectSphere[i][j]->noeudSphere->remove(); 
				vectSphere[i][j]->noeudSphere=NULL;
			}
		}
}

/**
 * Fonction determinant les mouvements des bulles mouvantes
 * en fonction de leurs caractéristiques
 * Les bulles mouvantes sont stockées dans une liste
 */
void Moteur::actionBullesMouvantes(){
	bool debut=false;
	for(itLstSphereMouventeB=lstSphereMouvante.begin(); 
			itLstSphereMouventeB!=lstSphereMouvante.end() ; 
			++itLstSphereMouventeB){

		if(debut){
			itLstSphereMouventeB--;
			debut=false;
		}
		//si bulle atteint destination
		if( (*itLstSphereMouventeB)->tempsAct >= 
				(*itLstSphereMouventeB)->tempsDestruction ){
			//si la destination d'une bulle mouvante n'est pas un bord de la grille
			if((*itLstSphereMouventeB)->x!=100 && 
					(*itLstSphereMouventeB)->y!=100)
				changerTailleSphere((*itLstSphereMouventeB)->x,
						(*itLstSphereMouventeB)->y, false);
			//cout<<(*itLstSphereMouventeB)->x<<"dirr"<<(*itLstSphereMouventeB)->y<<"cmpt"<<(*itLstSphereMouventeB)->tempsDestruction<<endl;
			(*itLstSphereMouventeB)->noeudBulle->remove();
			//supression du maillon
			delete (*itLstSphereMouventeB);
			itLstSphereMouventeB=
				lstSphereMouvante.erase(itLstSphereMouventeB);
			//si fin de liste retour
			if(itLstSphereMouventeB==lstSphereMouvante.end())return;
			//si debut de liste signal de correction a la prochaine iteration
			if(itLstSphereMouventeB!=lstSphereMouvante.begin()){
				debut=true;
				continue;
			}
			//sinon retour maillon precedant
			itLstSphereMouventeB--;
			continue;
		}

		//calcul de la position de la sphere en fonction du temps restant
		//taille d'une case ==> 1000 ms
		switch((*itLstSphereMouventeB)->direction){
			case BAS:
				(*itLstSphereMouventeB)->noeudBulle->
					setPosition(irr::core::vector3df(
								(*itLstSphereMouventeB)->noeudBulle->getPosition().X,
								(*itLstSphereMouventeB)->noeudBulle->getPosition().Y-2,
								0.0f) );
				break;
			case GAUCHE:
				(*itLstSphereMouventeB)->noeudBulle->
					setPosition(irr::core::vector3df(
								(*itLstSphereMouventeB)->noeudBulle->getPosition().X-2,
								(*itLstSphereMouventeB)->noeudBulle->getPosition().Y,
								0.0f) );
				break;
			case HAUT:
				(*itLstSphereMouventeB)->noeudBulle->
					setPosition(irr::core::vector3df(
								(*itLstSphereMouventeB)->noeudBulle->getPosition().X,
								(*itLstSphereMouventeB)->noeudBulle->getPosition().Y+2
								, 0.0f) );
				break;
			case DROITE:
				(*itLstSphereMouventeB)->noeudBulle->
					setPosition(irr::core::vector3df(
								(*itLstSphereMouventeB)->noeudBulle->getPosition().X+2,
								(*itLstSphereMouventeB)->noeudBulle->getPosition().Y,
								0.0f) );
				break;
			default:
				cout<<"erreur direction actions bulles"<<endl;
				break;
		}
		(*itLstSphereMouventeB)->tempsAct+=200;
	}

}

/**
 * Fonction permettant de creer les 4 bulles mouvantes
 * Aprés un éclatement 
 * L'origine des noeuds créés est récupéré sur le noeud case correspondant
 * trouvé grace aux aux coordonnées envoyées en paramètres
 * @param x : coordonnée abscisse d'origine des bulles mouvantes
 * @param y : coordonnée ordonnée d'origine des bulles mouvantes
 */
void Moteur::creerBulleMouvante(unsigned int x, unsigned int y){
	for(unsigned int i=0;i<4;++i){
		BulleMouvante *b=new BulleMouvante;
		b->x=(*itDestination)->coX;
		b->y=(*itDestination)->coY;
		b->noeudBulle = sceneManager->addSphereSceneNode	(	
				2.0f, // taille rayon f32
				16, //nombre de polycount?? s32
				0,// noeud parent
				-1, //id s32
				//		const core::vector3df &		position = 
				vectSphere[x][y]->noeudCase->getPosition(),
				//			const core::vector3df &		rotation = 
				irr::core::vector3df(0, 0, 0),
				//				const core::vector3df &		scale = 
				irr::core::vector3df(1.0f, 1.0f, 1.0f) 
				);	

		b->direction=(*itDestination)->direction;
		//VRR
		b->tempsDestruction=(*itDestination)->temps*1000;
		b->tempsAct=iterationAct;
		lstSphereMouvante.push_back(b);//memo du pointeur de la sphere dans la liste
		itDestination++;
	}
}


/**
 * Fonction permettant de vider le vector qui stocke les noeuds 
 * bulles en suprimmant 
 * les objet declaré dynamiquement
 */
void Moteur::viderVectBulle(){
	for(unsigned int j=0;j<vectSphere.size();j++)
		for(unsigned int i=0;i<vectSphere[j].size();i++){
			Bulle *a=vectSphere[i][j];
			delete a;
		}
}

/**
 * Destructeur de la class Moteur.
 * Appel de la fonction viderVectBulle
 */
Moteur::~Moteur(){
	viderVectBulle();
}
