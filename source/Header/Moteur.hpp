#ifndef MOT
#define MOT

#include <irrlicht/irrlicht.h>
#include "MyEvent.hpp"
#include <list>
#include <vector>
#include "Algo.hpp"
class Base;

/**
 * \struct Bulle
 * Structure contenant un pointeur vers un noeud bulle, son noeud case associé
 * ainsi que sa taille
 */
struct Bulle{
	irr::scene::IMeshSceneNode *noeudCase, *noeudSphere;
	unsigned int taille;
};

/**
 * \struct BulleMouvante
 * Structure contenant un pointeur vers un noeud bulle
 * La direction vers laquelle cette dernière bouge et le temps 
 * du moment de sa destruction
 */
struct BulleMouvante{
	irr::scene::IMeshSceneNode *noeudBulle;
	unsigned int direction, tempsDestruction;
	unsigned int x,y, tempsAct;
};

/**
 * \class Moteur
 * classe contenants tous les objets de la bibliotheque irrlicht
 * ainsi que toutes les fonctions qui gerent ces derniers
 * Cette classe contient également la boucle principalle du logiciel.
 */
class Moteur{
	private:
		Base *memBase;
		unsigned int iterationAct, coupRestant;
		bool actionEnCours, animEnCours;
		irr::IrrlichtDevice *device;
		irr::video::IVideoDriver* driver ;
		irr::scene::ISceneManager *sceneManager;
		irr::scene::ICameraSceneNode *camera;
		irr::scene::IMeshSceneNode* cube;
		irr::gui::IGUIEnvironment *gui;
		irr::gui::IGUIFont *font;
		irr::gui::IGUIStaticText *texte;
		irr::core::dimension2d<irr::u32 > tailleTexte;
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
		void liaisonBase(Base *a);
		bool initMoteur();
		bool launch();
		void viderVectBulle();
		void changerTailleSphere(unsigned int x, unsigned int y, bool lectAlg);
		void creerBulleMouvante(unsigned int x, unsigned int y);
		bool verifTabVide();
		void actionBullesMouvantes();
		void viderTabBulles();
		~Moteur();
};

#endif
