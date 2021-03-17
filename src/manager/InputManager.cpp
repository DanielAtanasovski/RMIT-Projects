#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::inputCallback(unsigned char key, int x, int y)
{
	//pressedKeys.push_front(key);
	// Search through function subscriptions for matching key's
	std::vector<keySubscription> foundSubscriptions = findSubscription(key);
	if (!foundSubscriptions.empty()) {
		// If more than one subscription found, loop through them all and call the
		// relevant callback
		for (keySubscription sub : foundSubscriptions) {
			char key = sub->first;
			sub->second(key);
		}
	}
}

void InputManager::subscribeToKeyPress(char key, std::function<void(char)> callback)
{
	keySubscription newSubscription = keySubscription();
	newSubscription->first = key;
	newSubscription->second = callback;
	keySubscriptions.push_back(newSubscription);
}

void InputManager::subscribeToKeysPress(char keys[], std::function<void(char)> callback)
{
	// todo
}

void InputManager::subscribeToKeyRelease(char key, std::function<void(char)> callback)
{
	//todo
}

void InputManager::subscribeToKeysRelease(char keys[], std::function<void(char)> callback)
{
	// todo
}

std::vector<keySubscription> InputManager::findSubscription(char key)
{
	std::vector<keySubscription> listOfValidSubscriptions = std::vector<keySubscription>();
	for(keySubscription sub : keySubscriptions)
	{
		if (sub->first == key) {
			listOfValidSubscriptions.push_back(sub);
		}
	}
	return listOfValidSubscriptions;
}

