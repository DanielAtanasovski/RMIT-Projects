#include "Input.h"
#include <iostream>

#if _WIN32
#   include <Windows.h>
#endif
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

std::vector<char> Input::keysPressed;
int Input::mouseLeft;
Vector2 Input::mousePosition = Vector2();
bool Input::waitForDifferentKey = false;

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

bool Input::onAnyKey() {
	if (keysPressed.size() > 0) {
		return true;
	}	
	return false;
}

void Input::onMouseCallback(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP)
			mouseLeft = 0;
		else
			mouseLeft = 1;
	}
	mousePosition.x = x;
	mousePosition.y = y;
}

void Input::onMouseMotionCallback(int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;
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

bool Input::onMouseLeftDown() {
	return mouseLeft;
}

Vector2 Input::getMousePosition()
{
	return mousePosition;
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
