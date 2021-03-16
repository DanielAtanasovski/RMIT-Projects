#pragma once
#include "Game.h"
/// <summary>
/// This class serves to pass callbacks from the GLUT engine to specific objects that require it
/// </summary>
class GlutCallbackInterface
{
public:
	static GlutCallbackInterface& getInstance() {
		static GlutCallbackInterface instance;
		return instance;
	}
	// Callbacks
	static void displayCallback();
	static void updateCallback();
	static void displayReshapeCallback(int width, int height);
	void setGame(Game* game);
	Game* getGame() { return game; };

private:
	GlutCallbackInterface() { }
	Game* game = nullptr;

};

