#include "MyEvent.hpp"


/**
 * Constructeur de la classe MyEventReceiver.
 * Initialisation du tableau d'entree
 */
MyEventReceiver::MyEventReceiver(){
	for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}

/**
 *	Fonction (surchargee) qui recupere l'evenement
 */
// Ceci est la méthode que nous devons implémenter
bool MyEventReceiver::OnEvent(const irr::SEvent& event){
	// Se souvient si la touche est enfoncée ou relâchée
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;
}

/**
 * Fonction verifaiant si une touche est enfoncee
 */
// Ceci est utilisé pour vérifier si une touche est enfoncée
bool MyEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const{
	return KeyIsDown[keyCode];
}

