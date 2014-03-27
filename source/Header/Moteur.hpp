#ifndef MOT
#define MOT

#include <irrlicht/irrlicht.h>
#include "MyEvent.hpp"
#include <list>
#include "Algo.hpp"


/**
 * @struct Bulle
 * Structure contenant un pointeur vers un noeud bulle
 * ses coordonnées sur le tableau 
 */
struct Bulle{
	irr::scene::IMeshSceneNode *noeudBulle;
	unsigned int x,y;
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
	unsigned int x,y;
};

/**
 * @class Moteur
 * classe contenants tous les objets de la bibliotheque irrlicht
 * ainsi que toutes les fonctions qui gerent ces derniers
 */
class Moteur{
	private:
unsigned int tempsCourrant;
		bool actionEnCours, animEnCours;
		irr::IrrlichtDevice *device;
		irr::video::IVideoDriver* driver ;
		irr::scene::ISceneManager *sceneManager;
		irr::scene::ICameraSceneNode *camera;
		irr::scene::IMeshSceneNode* cube, *grille;
	std::list<DestinationBulle*>::iterator itDestination;
		MyEventReceiver receiver;
		std::list<Bulle*> lstSphere;
		std::list<Bulle*>::iterator itLstSphere;
		std::list<BulleMouvante*> lstSphereMouvente;
		std::list<BulleMouvante*>::iterator itLstSphereMouvente,
		itLstSphereMouventeB;
		AnimList memListAnim;
	public:
		Moteur();
		void initSphere();
		bool initMoteur();
		bool launch();
		void viderListeBulle();
		void changerTailleSphere(std::list<Bulle*>::iterator it);
		void getItListBulle(unsigned int x, unsigned int y);
		void creerBulleMouvante(std::list<Bulle*>::iterator it);
		void actionBullesMouvantes();
		~Moteur();
};

#endif
