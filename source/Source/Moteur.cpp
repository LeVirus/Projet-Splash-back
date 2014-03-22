#include <iostream>
#include <vector>
#include "Moteur.hpp"
#include "Case.hpp"
#include "Grille.hpp"
#include "MyEvent.hpp"

using namespace std;

extern Grille *memGrille;

/**
 * Constructeur de la classe Moteur.
 *	appel de la fonction "initMoteur()"
 */
Moteur::Moteur(){
	initMoteur();
}

/**
 * Initialisation des objets necessaires au moteur
 * @return true tous les objets sont créés avec succés
 * @return false sinon
 */
bool Moteur::initMoteur(){

	// créer le moteur
	MyEventReceiver receiver;

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
		cout<<x<<" "<<y<<" "<<z<<endl;
		x+=10.0f;
		if(x>=60.0f){
			x=0.0f;
			y+=10.0f;
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

	sceneManager->addCameraSceneNodeFPS(       // ajout de la camera FPS
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
	irr::scene::IMeshSceneNode *sphere;         // pointeur vers le node
	irr::f32 x=0.0f ,y=0.0f,z=0.0f, tailleSphere;
	unsigned int taille;
	std::vector<std::vector<Case>> tmp=memGrille->getTabGrille();
	for(unsigned int j=0;j<tmp[i].size();j++)
		for(unsigned int i=0;i<tmp.size();i++){
			taille=tmp[i][j].getEtat();
			switch(taille){
				case 0:
					x+=10.0f;
					if(x>=60.0f){
						x=0.0f;
						y+=10.0f;
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
			a->noeudBulle=sphere;
			a->x=i;
			a->y=j;
			a->move=false;
			lstSphere.push_back(a);//memo du pointeur de la sphere dans la liste
			x+=10.0f;
			if(x>=60.0f){
				x=0.0f;
				y+=10.0f;
			}
		}

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
		scene->getSceneCollisionManager();
	MyEventReceiver receiver;

	//irr::core::vector3df nodePosition = 
		//(* lstSphere.begin() )->getPosition();//tmp
	while(device->run()) {


		if(receiver.IsKeyDown(irr::EMIE_LMOUSE_PRESSED_DOWN)){

		// Crée un rayon partant du curseur de la souris.
			ray = collisionManager->getRayFromScreenCoordinates(
						device->getCursorControl()->getPosition()
						, camera);


			irr::scene::IMeshSceneNode* node = 
				collisionManager->getSceneNodeAndCollisionPointFromRay(
						ray, outCollisionPoint, outTriangle);

	//si !node aucune collision avec un noeud
			if(node){
				for(itLstSphere=lstSphere.begin(); 
					itLstSphere!=lstSphere.end() ; ++itLstSphere){
					if((*itLstSphere)->move)continue;//si bulle mouvante
					if( (*itLstSphere)->noeudBulle == node ){
//identification du noeud
						memGrille->appliquerChangeCase(
							(*itLstSphere)->x, (*itLstSphere)->y);
//appel de la fonction dans Grille
						break;
					}
				}
				//recu quelque chose
			}
		}


/*		if(receiver.IsKeyDown(irr::KEY_KEY_W))
			nodePosition.Y += 2;//MOVEMENT_SPEED * frameDeltaTime;
		else if(receiver.IsKeyDown(irr::KEY_KEY_S))
			nodePosition.Y -=  2;//MOVEMENT_SPEED * frameDeltaTime;

		if(receiver.IsKeyDown(irr::KEY_KEY_A))
			nodePosition.X -=  2;//MOVEMENT_SPEED * frameDeltaTime;
		else if(receiver.IsKeyDown(irr::KEY_KEY_D))
			nodePosition.X +=  2;//MOVEMENT_SPEED * frameDeltaTime;

		(* lstSphere.begin() )->setPosition(nodePosition);
*/
		//tmp

		driver->beginScene (true, true,
				irr::video::SColor(255,255,255,255));
		sceneManager->drawAll ();
		driver->endScene ();
	}
	device->drop (); 
	return true;
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
