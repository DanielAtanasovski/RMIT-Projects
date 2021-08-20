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
		gltDeleteText(_resolutionText);
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
	void SetResolution(int width, int height) { _width = width; _height = height; }
	void SetScene(int scene) { _scene = scene; }
	void SetSubdivisions(int subdivisions) { _subdivisions = subdivisions; }
	void SetDrawAttributes(bool depth, bool lighting, bool cull) { _depth = depth; _lighting = lighting; _cull = cull; }
	void Draw();
	void UpdateState();
private:
	int _triangles = 0, _cubes = 0, _vertices = 0, _fps = 0,
	_width = 0, _height = 0, _scene = 0, _subdivisions = 0, _vertexData = 0;
	bool _depth = false, _lighting = false, _cull = false;
	GLTtext *_drawText, *_dataText, *_cubesText,
		*_fpsText, *_resolutionText, *_sceneText, *_subdivisionsText,
		*_attributesText;

	float xOffset = 2;
	float yOffset = 2;
	float yStep = 40;
	float scale = 2;
};