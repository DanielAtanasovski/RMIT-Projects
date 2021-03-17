#pragma once

#include <functional>
#include <vector>

typedef std::pair<char, std::function<void(char key)>>* keySubscription;

class InputManager
{
public:
	InputManager();
	~InputManager();
	void inputCallback(unsigned char key, int x, int y);

	// Functions that allow objects to subscribe to either one or multiple keys for a 
	// particular function callback
	void subscribeToKeyPress(char key, std::function<void(char)> callback);
	void subscribeToKeysPress(char keys[], std::function<void(char)> callback);
	void subscribeToKeyRelease(char key, std::function<void(char)> callback);
	void subscribeToKeysRelease(char keys[], std::function<void(char)> callback);

private:
	//std::list<char> pressedKeys
	std::vector<std::pair<char, std::function<void(char key)>>*> *keySubscriptions = new std::vector<std::pair<char, std::function<void(char key)>>*>();
	std::vector<std::pair<char, std::function<void(char key)>>*> findSubscription(char key);
};



