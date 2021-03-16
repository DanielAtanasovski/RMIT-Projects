#include "GlutCallbackInterface.h"
#include <stdio.h>


void GlutCallbackInterface::displayCallback()
{
	getInstance().getGame()->draw();
}

void GlutCallbackInterface::updateCallback()
{
	getInstance().getGame()->update();
}

// Callbacks
void GlutCallbackInterface::displayReshapeCallback(int width, int height)
{
	getInstance().getGame()->onReshape(width, height);
}


// Setters / getters

void GlutCallbackInterface::setGame(Game* game) {
	this->game = game;
	//getInstance().setGame(game);
}
