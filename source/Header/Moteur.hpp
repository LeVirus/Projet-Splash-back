#ifndef MOT
#define MOT

#include <list>
#include <irrlicht/irrlicht.h>

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
		irr::scene::IMeshSceneNode* cube, *grille;
		std::list<irr::scene::IMeshSceneNode*> lstSphere;
	public:
		Moteur();
		void initSphere();
		bool initMoteur();
		bool launch();
		~Moteur();
};

#endif
