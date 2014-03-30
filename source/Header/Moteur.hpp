#ifndef MOT
#define MOT

#include <irrlicht/irrlicht.h>
#include "MyEvent.hpp"
#include <list>
#include <vector>
#include "Algo.hpp"


/**
 * @struct Bulle
 * Structure contenant un pointeur vers un noeud bulle
 * ses coordonnées sur le tableau 
 */
struct Bulle{
	irr::scene::IMeshSceneNode *noeudCase, *noeudSphere;
};

/**
 * @struct BulleMouvante
 * Structure contenant un pointeur vers un noeud bulle
* La direction vers laquelle il bouge et le temps 
* du moment de la destruction
 */
struct BulleMouvante{
	irr::scene::IMeshSceneNode *noeudBulle;
	unsigned int direction, tempsDestruction;
	unsigned int x,y, tempsAct;
};

/**
 * @class Moteur
 * classe contenants tous les objets de la bibliotheque irrlicht
 * ainsi que toutes les fonctions qui gerent ces derniers
 */
class Moteur{
	private:
unsigned int tempsCourrant, iterationAct, tempsInter;
		bool actionEnCours, animEnCours;
		irr::IrrlichtDevice *device;
		irr::video::IVideoDriver* driver ;
		irr::scene::ISceneManager *sceneManager;
		irr::scene::ICameraSceneNode *camera;
		irr::scene::IMeshSceneNode* cube, *grille;
	std::list<DestinationBulle*>::iterator itDestination;
		MyEventReceiver receiver;
		std::vector< std::vector < Bulle* > > vectSphere;
		std::list<BulleMouvante*> lstSphereMouvante;
		std::list<BulleMouvante*>::iterator itLstSphereMouvante,
		itLstSphereMouventeB;
		AnimList memListAnim;
	public:
		Moteur();
		void initSphere();
		bool initMoteur();
		bool launch();
		void viderVectBulle();
		void changerTailleSphere(unsigned int x, unsigned int y, bool lectAlg);
		void creerBulleMouvante(unsigned int x, unsigned int y);
		void actionBullesMouvantes();
		~Moteur();
};

#endif
