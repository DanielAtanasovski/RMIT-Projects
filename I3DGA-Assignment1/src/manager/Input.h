#pragma once
#include <vector>
class Input
{
public:
	static void onKeyboardPressedCallback(char key, int x, int y);
	static void onKeyboardReleasedCallback(char key, int x, int y);
	static void OnMouseCallback(int button, int state, int x, int y);
	static bool onPressed(char key);
	static bool onReleased(char key);
	static bool onMouseLeftDown();
	static bool onAnyKey();

private:
	static void clearKeyFromKeys(char key);
	static int mouseLeft;
	static std::vector<char> keysPressed;
	static bool waitForDifferentKey;
};

 