#include "Input.h"
#include <iostream>

std::vector<char> Input::keysPressed;

void Input::onKeyboardPressedCallback(char key, int x, int y)
{
	// Check for quit
	if (key == 'q' || key == 27)
		exit(EXIT_SUCCESS);

	// If not already pressed
	if (std::find(keysPressed.begin(), keysPressed.end(), toupper(key)) == keysPressed.end())
		keysPressed.push_back(toupper(key));
}

void Input::onKeyboardReleasedCallback(char key, int x, int y)
{
	// Remove key from pressed keys list
	clearKeyFromKeys(toupper(key));
}

bool Input::onPressed(char key)
{
	for (size_t i = 0; i < keysPressed.size(); i++)
	{
		if (keysPressed[i] == toupper(key))
			return true;
	}
	return false;
}

bool Input::onReleased(char key)
{
	return !onPressed(toupper(key));
}

void Input::clearKeyFromKeys(char key)
{
	for (size_t i = 0; i < keysPressed.size(); i++)
	{
		if (keysPressed[i] == toupper(key)) {
			keysPressed.erase(keysPressed.begin() + i);
			return;
		}
	}
}
