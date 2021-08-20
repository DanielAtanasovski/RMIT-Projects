#include "HUD.h"

#include <sstream>

void HUD::Init() {
	gltInit();

	_drawText = gltCreateText();
	_dataText = gltCreateText();
	_cubesText = gltCreateText();
	_fpsText = gltCreateText();
	_resolutionText = gltCreateText();
	_sceneText = gltCreateText();
	_subdivisionsText = gltCreateText();
	_attributesText = gltCreateText();
};

void HUD::Draw()
{
	UpdateState();

	gltBeginDraw();
	gltColor(1, 0, 0, 1);

	gltDrawText2D(_fpsText, xOffset, yOffset, scale);
	gltDrawText2D(_resolutionText, xOffset, yOffset + (yStep * 1), scale);
	gltDrawText2D(_drawText, xOffset, yOffset + (yStep * 2), scale);
	gltDrawText2D(_dataText, xOffset, yOffset + (yStep * 3), scale);
	gltDrawText2D(_subdivisionsText, xOffset, yOffset + (yStep * 4), scale);
	gltDrawText2D(_attributesText, xOffset, yOffset + (yStep * 5), scale);
	gltDrawText2D(_sceneText, xOffset, yOffset + (yStep * 6), scale);

	gltEndDraw();
	glUseProgram(0);
}

void HUD::UpdateState()
{
	std::ostringstream stringStream;
	stringStream << "Cubes: " << _cubes << " | Triangles: " << _triangles << " | Vertices: " << _vertices;
	gltSetText(_drawText, stringStream.str().c_str());

	stringStream.str("");
	stringStream << "Data: " << _vertexData;
	gltSetText(_dataText, stringStream.str().c_str());

	stringStream.str("");
	stringStream << "FPS: " << _fps;
	gltSetText(_fpsText, stringStream.str().c_str());

	stringStream.str("");
	stringStream << "Resolution: " << _width << "x" << _height;
	gltSetText(_resolutionText, stringStream.str().c_str());

	stringStream.str("");
	stringStream << "Scene: " << _scene;
	gltSetText(_sceneText, stringStream.str().c_str());

	stringStream.str("");
	stringStream << "Subdivisions: " << _subdivisions;
	gltSetText(_subdivisionsText, stringStream.str().c_str());

	stringStream.str("");
	stringStream << "Lighting: " << _lighting << " | Depth Testing: " << _depth << " | Backface Culling: " << _cull;
	gltSetText(_attributesText, stringStream.str().c_str());
}
