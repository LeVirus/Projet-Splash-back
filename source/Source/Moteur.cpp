#include "Moteur.hpp"



Moteur::Moteur(){
	initMoteur();
}

bool Moteur::initMoteur(){
	device = irr::createDevice (
			irr::video::EDT_OPENGL,
			irr::core::dimension2d<irr::u32>(800,600),
			32,
			false,
			true,
			false,
			0);
	driver = device->getVideoDriver();
	sceneManager = device->getSceneManager ();
	//sceneManager = irr::core::vector3df (5,0,0)); // scene manager		



	/*cube =         // pointeur vers le node
		sceneManager->addCubeSceneNode(        // la creation du cube
				10.0f,                             // cote de 10 unites
				0,                                 // parent = racine
				-1,                                // pas d'ID
				irr::core::vector3df(              // le vecteur de position
					0.0f,                          // origine en X
					0.0f,                          // origine en Y
					20.0f));*/                       // +20 unites en Z

	//cube->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
	grille=sceneManager->addMeshSceneNode (sceneManager->getMesh ("Ressources/Grille.obj"));//0 noeud parent(racine)
	grille->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
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

}

bool Moteur::launch(){
	while(device->run()) {
		driver->beginScene (true, true,
				irr::video::SColor(255,255,255,255));
		sceneManager->drawAll ();
		driver->endScene ();
	}
	device->drop (); 
}

Moteur::~Moteur(){

}
