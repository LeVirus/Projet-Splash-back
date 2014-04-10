#include "MyEvent.hpp"


/**
 * Constructeur de la classe MyEventReceiver.
 * Initialisation du tableau d'entree
 */
MyEventReceiver::MyEventReceiver(){
	for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
	MouseState.LeftButtonDown=false;
}

/**
 *  Fonction renvoyant LeftButtonDown si le bouton 
 *  gauche de la souris est pressé
 *  return true : indefinis
 *  return false : indefinis
 */
bool MyEventReceiver::leftButtonIsPressed(){
	return MouseState.LeftButtonDown;
}

/**
 *	Fonction (surchargee) qui recupere l'evenement courrant
 *  return true : si LeftButtonDown est à true
 *  return false : si LeftButtonDown est à false
 */
bool MyEventReceiver::OnEvent(const irr::SEvent& event){
	// Se souvient si la touche est enfoncée ou relâchée
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	// Se rappelle de l'état de la souris.
	else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT){
		switch(event.MouseInput.Event){
			case irr::EMIE_LMOUSE_PRESSED_DOWN:
				MouseState.LeftButtonDown = true;
				break;

			case irr::EMIE_LMOUSE_LEFT_UP:
				MouseState.LeftButtonDown = false;
				break;

			case irr::EMIE_MOUSE_MOVED:
				MouseState.Position.X = event.MouseInput.X;
				MouseState.Position.Y = event.MouseInput.Y;
				break;

			default:
				// Nous n'utiliserons pas la roulette.
				break;
		}
	}


	return false;
}

/**
 * Fonction verifaiant si une touche est enfoncee
 * @return true : si la touche est enfoncée
 * @return false :si la touche n'est pas enfoncée
 */
bool MyEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const{
	return KeyIsDown[keyCode];
}

