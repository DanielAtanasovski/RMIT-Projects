#include "HUD.h"

#include <sstream>

void HUD::Init() {
	gltInit();

	_drawText = gltCreateText();
	_dataText = gltCreateText();
	_cubesText = gltCreateText();
	_fpsText = gltCreateText();
	_displayText = gltCreateText();
	_sceneText = gltCreateText();
	_subdivisionsText = gltCreateText();
	_attributesText = gltCreateText();
};

void HUD::Draw()
{
	UpdateState();

	gltBeginDraw();
	gltColor(1, 0, 0, 1);

	gltDrawText2D(_fpsText, _xOffset, _yOffset, _scale);
	if (_fullHUD) {
		gltDrawText2D(_displayText, _xOffset, _yOffset + (_yStep * 1), _scale);
		gltDrawText2D(_drawText, _xOffset, _yOffset + (_yStep * 2), _scale);
		gltDrawText2D(_dataText, _xOffset, _yOffset + (_yStep * 3), _scale);
		gltDrawText2D(_subdivisionsText, _xOffset, _yOffset + (_yStep * 4), _scale);
		gltDrawText2D(_attributesText, _xOffset, _yOffset + (_yStep * 5), _scale);
		gltDrawText2D(_sceneText, _xOffset, _yOffset + (_yStep * 6), _scale);
	}

	gltEndDraw();
	glUseProgram(0);
}

void HUD::UpdateState()
{
	std::ostringstream stringStream;
	stringStream << "Cubes: " << ValueToThousandsSeperator(_cubes) << " | Triangles: "
		<< ValueToThousandsSeperator(_triangles) << " | Vertices: " 
		<< ValueToThousandsSeperator(_vertices);
	gltSetText(_drawText, stringStream.str().c_str());

	stringStream.str("");
	stringStream << "Data: " << ValueToThousandsSeperator(_vertexData) << " bytes";
	gltSetText(_dataText, stringStream.str().c_str());

	stringStream.str("");
	stringStream << "FPS: " << _fps;
	gltSetText(_fpsText, stringStream.str().c_str());

	stringStream.str("");
	stringStream << "Resolution: " << _width << "x" << _height << " " << _refreshRate << "Hz";
	gltSetText(_displayText, stringStream.str().c_str());

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

std::string HUD::ValueToThousandsSeperator(unsigned int data)
{
	std::string retValue = std::to_string(data);
	int seperator = retValue.length() - 3;
	while (seperator > 0) {
		retValue.insert(seperator, ",");
		seperator -= 3;
	}
	return retValue;
}
