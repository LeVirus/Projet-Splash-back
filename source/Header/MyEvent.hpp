#ifndef MYE 
#define MYE

#include <irrlicht/irrlicht.h>

/**
 * @class MyEventReceiver
 * Classe fille de IEventReceiver (irrlicht)
 *	Recupere les evenement souris et les traite
 */
class MyEventReceiver: public irr::IEventReceiver{
	private:
		// Nous utilisons ce tableau pour stocker l'état de chaque touche.
		bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	public:


		// Nous créons une structure pour enregistrer les informations sur l'état de la souris.
/**
 * @struct SMouseState
 * Stocke les informations sur l'état de la souris
 */
		struct SMouseState{
			irr::core::position2di Position;
			bool LeftButtonDown, RightButtonDown;
			SMouseState() : LeftButtonDown(false) { }
		} MouseState;


		MyEventReceiver();
		virtual bool OnEvent(const irr::SEvent& event);
		virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
		bool leftButtonIsPressed();
		bool rightButtonIsPressed();
};

#endif
