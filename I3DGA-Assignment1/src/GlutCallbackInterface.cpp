#include "GlutCallbackInterface.h"
#include "manager/Input.h"

/// <summary>
/// Serve as a way to call methods of objects in c++ rather than static functions
/// </summary>
Game* GlutCallbackInterface::gameInstance;

void GlutCallbackInterface::displayCallback()
{
	GlutCallbackInterface::gameInstance->draw();
}

void GlutCallbackInterface::updateCallback()
{
	GlutCallbackInterface::gameInstance->update();
}

void GlutCallbackInterface::mouseFuncCallback(int button, int state, int x, int y) {
	Input::OnMouseCallback(button, state, x, y);
}

void GlutCallbackInterface::keyboardPressedCallback(unsigned char key, int x, int y)
{
	Input::onKeyboardPressedCallback(key, x, y);
}

void GlutCallbackInterface::keyboardReleasedCallback(unsigned char key, int x, int y) 
{
	Input::onKeyboardReleasedCallback(key, x, y);
}

void GlutCallbackInterface::displayReshapeCallback(int width, int height)
{
	GlutCallbackInterface::gameInstance->onReshape(width, height);
}

// Setters / getters
void GlutCallbackInterface::setGame(Game* game) {
	GlutCallbackInterface::gameInstance = game;
}
