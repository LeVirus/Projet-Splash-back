#include <iostream>
#include <vector>
#include <ctime>
#include "Moteur.hpp"
#include "Case.hpp"
#include "Grille.hpp"
#include "constantes.hpp"

using namespace std;

extern Grille *memGrille;
extern Algo *memoAlgo;

/**
 * Constructeur de la classe Moteur.
 *	appel de la fonction "initMoteur()"
 */
Moteur::Moteur(){
	animEnCours=false;
	actionEnCours=false;
	initMoteur();
}

/**
 * Initialisation des objets necessaires au moteur
 * @return true tous les objets sont créés avec succés
 * @return false sinon
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
	//sceneManager = irr::core::vector3df (5,0,0)); // scene manager		


	irr::scene::IMeshSceneNode* cube;         // pointeur vers le node
	irr::f32 x=0.0f ,y=0.0f,z=0.0f;
	for(unsigned int i=0;i<36;++i){
		cube=sceneManager->addCubeSceneNode(        // la creation du cube
				10.0f,                             // cote de 10 unites
				0,                                 // parent = racine
				-1,                                // pas d'ID
				irr::core::vector3df(              // le vecteur de position
					x,                          // origine en X
					y,                          // origine en Y
					z));                       // +20 unites en Z
		cube->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
		//cout<<x<<" "<<y<<" "<<z<<endl;
		x+=10.0f;
		if(x>=60.0f){
			x=0.0f;
			y-=10.0f;
		}
	}


	//grille=sceneManager->addMeshSceneNode (sceneManager->getMesh ("Ressources/Grille.obj"));//0 noeud parent(racine)
	//grille->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
	//1 id

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
	keyMap[4].Action = irr::EKA_JUMP_UP;       // saut
	keyMap[4].KeyCode = irr::KEY_SPACE;        // barre espace

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
 * Procedure d'initialisation des spheres a l'affichage
 * Lis les donnees dans la classe Grille
 */
void Moteur::initSphere(){
cerr<<"debut initS"<<endl;
	irr::scene::IMeshSceneNode *sphere;         // pointeur vers le node
	irr::f32 x=0.0f ,y=0.0f,z=0.0f, tailleSphere;
	unsigned int taille;
	std::vector<std::vector<Case>> tmp=memGrille->getTabGrille();
	for(unsigned int j=0;j<tmp.size();j++)
		for(unsigned int i=0;i<tmp[j].size();i++){
			taille=tmp[i][j].getEtat();
			switch(taille){
				case 0:
					x+=10.0f;
					if(x>=60.0f){
						x=0.0f;
						y-=10.0f;
					}
					continue;
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
			Bulle *a=new Bulle;
			irr::scene::ITriangleSelector *triangleCol=
				sceneManager->createOctreeTriangleSelector(
						sphere->getMesh(), sphere, 128);
			a->noeudBulle=sphere;
			a->x=i;
			a->y=j;

			sphere->setTriangleSelector(triangleCol);
			triangleCol->drop();
			if(a)cout<<"deeede"<<endl;

			lstSphere.push_back(a);//memo du pointeur de la sphere dans la liste
			cout<<"deeede"<<endl;
			x+=10.0f;
			if(x>=60.0f){
				x=0.0f;
				y-=10.0f;
			}
		}
cerr<<"fin initS"<<endl;

}

/**
 * Boucle générale du moteur physique
 * @return false si la fonction a fermer suite à un problème
 * @return true Si la fonction a fermer aprés avoir reçu un signal d'arret
 */
bool Moteur::launch(){
	irr::core::vector3df outCollisionPoint;
	irr::core::triangle3df outTriangle;
	irr::core::line3df ray; 
	irr::scene::ISceneCollisionManager* collisionManager = 
		sceneManager->getSceneCollisionManager();
	unsigned int tempsInit; 
	std::list<OrigineEclatement*>::iterator itOrigine;
	//irr::core::vector3df nodePosition = 
	//(* lstSphere.begin() )->getPosition();//tmp
	while(device->run()) {
		if( !receiver.leftButtonIsPressed() )actionEnCours=false;
		//attendre que le bouton soit relacher pour reinitialiser
		//la variable




		//Animations ________________________________________________
		if(animEnCours){
			tempsCourrant=clock()-tempsInit;
			cout<<tempsCourrant<<"temps"<<endl;
			//comparaison du temps actuel convertis en secondes avec le temps
			//du point Origine de l'eclatement
			while( itOrigine!=memListAnim.memListOrigine->end() 
					&&	(*itOrigine)->tempsO<=tempsCourrant/1000){
				//recup de l'iterator correspondant
				getItListBulle( (*itOrigine)->coXO, (*itOrigine)->coYO );
				changerTailleSphere( itLstSphere );
				creerBulleMouvante(itLstSphere);
				actionBullesMouvantes();
				itOrigine++;
				//pusher les 4 spheres mouvantes
				//creer une nouvelle liste
			}
			if( itOrigine == memListAnim.memListOrigine->end() ){//tmp____

				animEnCours=false;
			}
		}

		//Animations ________________________________________________




		//action souris________________________________________________

		if(!actionEnCours  && !animEnCours  &&  receiver.leftButtonIsPressed()){
			actionEnCours=true;
			cerr<<"left detected"<<endl;
			// Crée un rayon partant du curseur de la souris.
			ray = collisionManager->getRayFromScreenCoordinates(
					device->getCursorControl()->getPosition()
					, camera);

			irr::scene::ISceneNode* node = 
				collisionManager->getSceneNodeAndCollisionPointFromRay(
						ray, outCollisionPoint, outTriangle);

			//si !node aucune collision avec un noeud
			if(node){
				cerr<<"node detected"<<endl;
				for(itLstSphere=lstSphere.begin(); 
						itLstSphere!=lstSphere.end() ; ++itLstSphere){
					if( (*itLstSphere)->noeudBulle == node ){
						//identification du noeud
						memGrille->appliquerChangeCase(
								(*itLstSphere)->x, (*itLstSphere)->y);


						//si eclatement_________________________________________
						if( memGrille->getTabValue( 
									(*itLstSphere)->x, (*itLstSphere)->y )
								== 0 ){
							memListAnim=memoAlgo->getListAnim();
							itOrigine=memListAnim.memListOrigine->begin();
							itDestination=memListAnim.memListDestination->begin();
							tempsInit=clock();//init du chrono
							animEnCours=true;
						}

						//si aucun eclatement____________________________________
						else{
							changerTailleSphere( itLstSphere );
						}

						memGrille->afficherGrille();
						//appel de la fonction dans Grille
						break;
					}
				}
			}

		}

		//action souris________________________________________________







		driver->beginScene (true, true,
				irr::video::SColor(255,255,255,255));
		sceneManager->drawAll ();
		driver->endScene ();


	}

	//cerr<<"ss"<<endl;
	device->drop (); 
	return true;
}


/**
 * Fonction permettant de recuperer l'iterator correspondant aux
 * coordonnees envoyees en argument 
 * L'iterator est memorise dans itLstSphere
 */
void Moteur::getItListBulle(unsigned int x, unsigned int y){
	for(itLstSphere=lstSphere.begin(); 
			itLstSphere!=lstSphere.end() ; ++itLstSphere){
		if( (*itLstSphere)->x==x  &&  (*itLstSphere)->y==y )return;
	}
	cout<<"erreur bulle non trouvee getItListBulle"<<endl;
}


/**
 * Fonction permettant de changer graphiquement la taille d'une sphere
 * (en fonction de sa taille actuelle)
 */
void Moteur::changerTailleSphere(std::list<Bulle*>::iterator it){
	unsigned int tailleSphere;
	if(!(*it)){
		cout<<"erreur pointeur changerTailleSphere"<<endl;
		return;
	}
	Bulle *b=new Bulle;
	b->x=(*it)->x;
	b->y=(*it)->y;
	switch( memGrille->getTabValue(b->x, b->y) ){
		case 0:
			//(*it)->noeudBulle->setVisible (false);
			return;
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
		default:
			cerr<<"erreur taille non valide initSphere"<<endl;
			break;
	}
	b->noeudBulle = sceneManager->addSphereSceneNode	(	


			tailleSphere,  //taille rayon f32
			16, //nombre de polycount?? s32
			0,// noeud parent
			-1, //id s32
			//		const core::vector3df &		position = 
			(*it)->noeudBulle->getPosition(),
			//			const core::vector3df &		rotation = 
			irr::core::vector3df(0, 0, 0),
			//				const core::vector3df &		scale = 
			irr::core::vector3df(1.0f, 1.0f, 1.0f) 
			);	
	irr::scene::ITriangleSelector *triangleCol=
		sceneManager->createOctreeTriangleSelector(
				b->noeudBulle->getMesh(), b->noeudBulle, 128);
	b->noeudBulle->setTriangleSelector(triangleCol);
	triangleCol->drop();


	lstSphere.push_back(b);//memo du pointeur de la sphere dans la liste

	(*it)->noeudBulle->remove();
	delete (*it);
	lstSphere.erase(it);
}

/**
 * Fonction determinant les mouvements des bulles mouvantes
 */
void Moteur::actionBullesMouvantes(){
	double tmp;
	for(itLstSphereMouventeB=lstSphereMouvente.begin(); 
			itLstSphereMouventeB!=lstSphereMouvente.end() ; 
			++itLstSphereMouventeB){
		//calcul de la position de la sphere en fonction du temps restant
		//taille d'une case ==> 1000 ms
		tmp=(  (*itLstSphereMouventeB)->tempsDestruction - 
				tempsCourrant) / 1000 * TAILLE_CASE;
		switch((*itLstSphereMouventeB)->direction){
			case BAS:
				(*itLstSphereMouventeB)->noeudBulle->
					setPosition(irr::core::vector3df(
								(*itLstSphereMouventeB)->x*TAILLE_CASE,
								(*itLstSphereMouventeB)->y*TAILLE_CASE + 
								tmp , 0.0f) );
				break;
			case GAUCHE:
				(*itLstSphereMouventeB)->noeudBulle->
					setPosition(irr::core::vector3df(
								(*itLstSphereMouventeB)->x*TAILLE_CASE + tmp,
								(*itLstSphereMouventeB)->y*TAILLE_CASE  , 
								0.0f) );
				break;
			case HAUT:
				(*itLstSphereMouventeB)->noeudBulle->
					setPosition(irr::core::vector3df(
								(*itLstSphereMouventeB)->x*TAILLE_CASE,
								(*itLstSphereMouventeB)->y*TAILLE_CASE - 
								tmp , 0.0f) );
				break;
			case DROITE:
				(*itLstSphereMouventeB)->noeudBulle->
					setPosition(irr::core::vector3df(
								(*itLstSphereMouventeB)->x*TAILLE_CASE - tmp,
								(*itLstSphereMouventeB)->y*TAILLE_CASE,  
								0.0f) );
				break;
			default:
				cout<<"erreur direction actions bulles"<<endl;
				break;
		}
	}
}

/**
 * Fonction permettant de creer les 4 bulles mouvantes
 * a partir d'un eclatement 
 */
void Moteur::creerBulleMouvante(std::list<Bulle*>::iterator it ){
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
				(*it)->noeudBulle->getPosition(),
				//			const core::vector3df &		rotation = 
				irr::core::vector3df(0, 0, 0),
				//				const core::vector3df &		scale = 
				irr::core::vector3df(1.0f, 1.0f, 1.0f) 
				);	

		b->direction=(*itDestination)->direction;
		b->tempsDestruction=(*itDestination)->temps*1000+tempsCourrant;
		lstSphereMouvente.push_back(b);//memo du pointeur de la sphere dans la liste
		itDestination++;
	}
}


/**
 * Fonction permettant de vider la liste en suprimmant 
 * les objet declaré dynamiquement
 */
void Moteur::viderListeBulle(){
	while( !lstSphere.empty() ){
		delete (* lstSphere.begin() ) -> noeudBulle;
		lstSphere.erase( lstSphere.begin() );
	}
}

/**
 * Destructeur de la class Moteur.  
 */
Moteur::~Moteur(){
	viderListeBulle();
}
