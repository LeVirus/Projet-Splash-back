#include <irrlicht/irrlicht.h>

class Moteur{
	private:
		irr::IrrlichtDevice *device;
		irr::video::IVideoDriver* driver ;
		irr::scene::ISceneManager *sceneManager;
irr::scene::IMeshSceneNode* cube, *grille;
	public:
		Moteur();
		bool initMoteur();
		bool launch();
		~Moteur();
};
