#ifndef MOT
#define MOT

#include <irrlicht/irrlicht.h>
#include "MyEvent.hpp"
#include <list>


/**
 * @struct Bulle
 * Structure contenant un pointeur vers un noeud bulle
 * ses coordonnées sur le tableau et un booleen determinant 
 * si le noeud est mouvant
 */
struct Bulle{
	irr::scene::ISceneNode *noeudBulle;
	irr::scene::ITriangleSelector *triangleCol;
	unsigned int x,y;
	bool move;
};

/**
 * @class Moteur
 * classe contenants tous les objets de la bibliotheque irrlicht
 * ainsi que toutes les fonctions qui gerent ces derniers
 */
class Moteur{
	private:
		irr::IrrlichtDevice *device;
		irr::video::IVideoDriver* driver ;
		irr::scene::ISceneManager *sceneManager;
		irr::scene::ICameraSceneNode *camera;
		irr::scene::IMeshSceneNode* cube, *grille;
		MyEventReceiver receiver;
		std::list<Bulle*> lstSphere;
		std::list<Bulle*>::iterator itLstSphere;
	public:
		Moteur();
		void initSphere();
		bool initMoteur();
		bool launch();
		void viderListeBulle();
		~Moteur();
};

#endif
