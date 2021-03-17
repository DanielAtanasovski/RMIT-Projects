#include "GlutCallbackInterface.h"

void GlutCallbackInterface::displayCallback()
{
	getInstance().getGame()->draw();
}

void GlutCallbackInterface::updateCallback()
{
	getInstance().getGame()->update();
}

void GlutCallbackInterface::inputCallback(unsigned char key, int x, int y)
{
	getInstance().getGame()->getInputManager().inputCallback(key, x, y);
}

// Callbacks
void GlutCallbackInterface::displayReshapeCallback(int width, int height)
{
	getInstance().getGame()->onReshape(width, height);
}

// Setters / getters
void GlutCallbackInterface::setGame(Game* game) {
	this->game = game;
}
