#pragma once
#include "Game.h"

/// <summary>
/// This class serves to pass callbacks from the GLUT engine to specific objects that require it
/// </summary>
class GlutCallbackInterface
{
public:
	// Callbacks
	static void displayCallback();
	static void updateCallback();
	static void mouseFuncCallback(int button, int state, int x, int y);
	static void keyboardPressedCallback(unsigned char key, int x, int y);
	static void keyboardReleasedCallback(unsigned char key, int x, int y);
	static void mouseMotionCallback(int x, int y);
	static void displayReshapeCallback(int width, int height);
	static void setGame(Game* game);

private:
	GlutCallbackInterface() { gameInstance = nullptr; }
	static Game* gameInstance;
};

