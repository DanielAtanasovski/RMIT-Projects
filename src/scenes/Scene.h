#pragma once
#include <vector>
#include "../drawing/Shapes.h"

class Scene
{
public:
	Scene() {};
	~Scene() {};
	virtual void Init() {}; // Initialise
	virtual void Run() {}; // Loop
	virtual void Done() {}; // Unbind stuff
	virtual void Recalculate() abstract;

	// Toggles
	void ToggleLighting();
	void ToggleCullFaces();
	void ToggleDepthTest();

	// Getters / Setters
	int GetSubdivisions() { return _subdivisions; }
	void SetSubdivisions(int subdivisions) { _subdivisions = subdivisions; };

protected:
	int _subdivisions = 0;
	bool _cullFaces = true;
	bool _depthTest = true;
	bool _lighting = false;
	int _triangleCount = 0;


};