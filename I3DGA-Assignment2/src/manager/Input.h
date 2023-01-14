#pragma once
#include <vector>
#include "../math/Vector2.h"
class Input
{
public:
	static void onKeyboardPressedCallback(char key, int x, int y);
	static void onKeyboardReleasedCallback(char key, int x, int y);
	static void onMouseCallback(int button, int state, int x, int y);
	static void onMouseMotionCallback(int x, int y);
	static bool onPressed(char key);
	static bool onReleased(char key);
	static bool onMouseLeftDown();
	static Vector2 getMousePosition();
	static bool onAnyKey();

private:
	static void clearKeyFromKeys(char key);
	static int mouseLeft;
	static Vector2 mousePosition;
	static std::vector<char> keysPressed;
	static bool waitForDifferentKey;
};

 