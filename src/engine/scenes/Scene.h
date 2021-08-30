#pragma once

#include <vector>

class Scene
{
public:
	// Scene
	Scene() {};
	virtual void Init() = 0; // Initialise
	virtual void Update(unsigned int td_milli) = 0; // Use to update with delta
	virtual void Run() = 0; // Loop
	virtual void Done() = 0; // Unbind stuff

protected:
	virtual void Draw() {};
};