#pragma once

#include <glad/glad.h>

#define GLT_IMPLEMENTATION
#include <gltext.h>

#include <iostream>

class HUD {
public:
	HUD() {};
	~HUD() {
		gltDeleteText(_drawText);
		gltDeleteText(_dataText);
		gltDeleteText(_cubesText);
		gltDeleteText(_fpsText);
		gltDeleteText(_displayText);
		gltDeleteText(_sceneText);
		gltDeleteText(_subdivisionsText);
		gltDeleteText(_attributesText);
		gltTerminate();
	};
	void Init();

	void SetData(int triangles, int cubes, int vertices, int vertexData) { 
		_triangles = triangles; 
		_cubes = cubes; 
		_vertices = vertices; 
		_vertexData = vertexData;
	}

	void SetFPS(int fps) { _fps = fps; }
	void SetDisplay(int width, int height, int refreshRate) { _width = width; _height = height; _refreshRate = refreshRate; }
	void SetScene(int scene) { _scene = scene; }
	void SetSubdivisions(int subdivisions) { _subdivisions = subdivisions; }
	void SetDrawAttributes(bool depth, bool lighting, bool cull) { _depth = depth; _lighting = lighting; _cull = cull; }
	void ToggleFullHUD() {
		_fullHUD = !_fullHUD;
	}
	void Draw();
	void UpdateState();
private:
	int _triangles = 0, _cubes = 0, _vertices = 0, _fps = 0, _refreshRate = 0,
	_width = 0, _height = 0, _scene = 0, _subdivisions = 0, _vertexData = 0;
	bool _depth = false, _lighting = false, _cull = false;
	GLTtext *_drawText, *_dataText, *_cubesText,
		*_fpsText, *_displayText, *_sceneText, *_subdivisionsText,
		*_attributesText;

	float _xOffset = 2;
	float _yOffset = 2;
	float _yStep = 40;
	float _scale = 2;

	bool _fullHUD = true;

	std::string ValueToThousandsSeperator(unsigned int data);
};