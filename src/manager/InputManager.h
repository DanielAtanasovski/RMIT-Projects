#pragma once
#include <list>
#include <functional>
#include <vector>

typedef std::pair<char, std::function<void(char key)>>* keySubscription;
//typedef std::vector<char, std::function<void()>>* keySubscription;

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
	std::vector<keySubscription> keySubscriptions = std::vector<keySubscription>();
	std::vector<keySubscription> findSubscription(char key);
};



