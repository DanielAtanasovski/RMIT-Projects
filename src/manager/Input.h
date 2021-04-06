#pragma once
#include <vector>
class Input
{
public:
	static void onKeyboardPressedCallback(char key, int x, int y);
	static void onKeyboardReleasedCallback(char key, int x, int y);
	static bool onPressed(char key);
	static bool onReleased(char key);

private:
	static void clearKeyFromKeys(char key);
	static std::vector<char> keysPressed;
};

