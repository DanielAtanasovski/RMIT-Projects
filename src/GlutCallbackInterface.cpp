#include "GlutCallbackInterface.h"
#include "manager/Input.h"

Game* GlutCallbackInterface::gameInstance;

void GlutCallbackInterface::displayCallback()
{
	GlutCallbackInterface::gameInstance->draw();
	//getInstance().getGame()->draw();
}

void GlutCallbackInterface::updateCallback()
{
	GlutCallbackInterface::gameInstance->update();
	//getInstance().getGame()->update();
}

void GlutCallbackInterface::keyboardPressedCallback(unsigned char key, int x, int y)
{
	Input::onKeyboardPressedCallback(key, x, y);
	//getInstance().getGame()->getInputManager().inputCallback(key, x, y);
}

void GlutCallbackInterface::keyboardReleasedCallback(unsigned char key, int x, int y) 
{
	Input::onKeyboardReleasedCallback(key, x, y);
}

// Callbacks
void GlutCallbackInterface::displayReshapeCallback(int width, int height)
{
	GlutCallbackInterface::gameInstance->onReshape(width, height);
}

// Setters / getters
void GlutCallbackInterface::setGame(Game* game) {
	GlutCallbackInterface::gameInstance = game;
}
