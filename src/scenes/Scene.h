#pragma once

#include <vector>
#include "../drawing/Shapes.h"
#include "../drawing/HUD.h"

class Scene
{
public:
	Scene() {};
	~Scene() {};
	virtual void Init(HUD* hud) {}; // Initialise
	virtual void Run() {}; // Loop
	virtual void Done() {}; // Unbind stuff
	virtual void Recalculate() abstract;

	// Toggles
	void ToggleLighting();
	bool isLighting() { return _lighting; }
	void ToggleCullFaces();
	bool isCulling() { return _cullFaces; }
	void ToggleDepthTest();
	bool isDepthTesting() { return _depthTest; }

	// Getters / Setters
	int GetSubdivisions() { return _subdivisions; }
	void SetSubdivisions(int subdivisions) { _subdivisions = subdivisions; };

protected:
	HUD* _hud = nullptr;

	int _subdivisions = 0;
	bool _cullFaces = true;
	bool _depthTest = true;
	bool _lighting = false;
	int _triangleCount = 0;
};