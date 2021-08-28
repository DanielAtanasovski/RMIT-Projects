#include "Scene1.h"
#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <string>


void Scene1::Init(HUD* hud, Camera* camera)
{
	_hud = hud;
	_camera = camera;
	_camera->UpdatePosition(glm::vec3(0, 0, 25));

	_lighting = false;
	_cullFaces = true;
	_depthTest = true;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	_hud->SetDrawAttributes(_depthTest, _lighting, _cullFaces);
	_hud->SetSubdivisions(_subdivisions);

	// Directional Camera
	GLfloat ambient[] = { 0.5, 0.5, 0.4, 0.2 };
	GLfloat diffuse[] = { 0.5, 0.5, 0.2, 0.2 };
	GLfloat specular[] = { 0.4, 0.4, 0.4, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);

	Recalculate();
}

void Scene1::Run()
{	
	glPushMatrix();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(glm::value_ptr(_camera->getPerspectiveMatrix()));

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// Set View Matrix
	glLoadMatrixf(glm::value_ptr(_camera->getViewMatrix()));

	// Draw Axis
	glBegin(GL_LINES);

	// X-AXIS
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);

	// Y-AXIS
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -10.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);

	// Z-AXIS
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(0.0f, 0.0f, 10.0f);

	glEnd();

	Draw();

	glPopMatrix();
}

void Scene1::Done()
{
	glDisable(GL_LIGHTING);

	_verticesArray.clear();
	_verticesArray.shrink_to_fit();
	_facesArray.clear();
	_facesArray.shrink_to_fit();
	_materialIds.clear();
	_materialIds.shrink_to_fit();

	_triangleCount = 0;
	_cubeCount = 0;
	_subdivisions = 0;
}

void Scene1::Draw()
{
	glPushMatrix();

	if (_lighting)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);

	// Draw Shape
	glBegin(GL_TRIANGLES);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	int lastMatIndex = 99;
	for (size_t i = 0; i < _facesArray.size(); i++)
	{
		// Get Triangle Vertexes
		glm::ivec3 faceIndex = _facesArray[i];
		glm::vec3 pointA = _verticesArray[faceIndex.x];
		glm::vec3 pointB = _verticesArray[faceIndex.y];
		glm::vec3 pointC = _verticesArray[faceIndex.z];

		// Material TODO: Remove the complications and just make it simpler
		// AKA - if X-Axis (pointA.x == pointB.x == pointC.x) use material 0 etc...
		Material material = _CUBE_MATERIALS[_materialIds[i*3]];
		if (_lighting)
		{ 
			if (_materialIds[i*3] != lastMatIndex) {
			
				// Ambient
				GLfloat materialConvert[] = { 0, 0, 0, 0 };
				materialConvert[0] = material.GetAmbient().r;
				materialConvert[1] = material.GetAmbient().g;
				materialConvert[2] = material.GetAmbient().b;
				materialConvert[3] = material.GetAmbient().a;
				glMaterialfv(GL_FRONT, GL_AMBIENT, materialConvert);

				// Diffuse
				materialConvert[0] = material.GetDiffuse().r;
				materialConvert[1] = material.GetDiffuse().g;
				materialConvert[2] = material.GetDiffuse().b;
				materialConvert[3] = material.GetDiffuse().a;
				glMaterialfv(GL_FRONT, GL_DIFFUSE, materialConvert);

				// Specular
				materialConvert[0] = material.GetSpecular().r;
				materialConvert[1] = material.GetSpecular().g;
				materialConvert[2] = material.GetSpecular().b;
				materialConvert[3] = material.GetSpecular().a;
				glMaterialfv(GL_FRONT, GL_SPECULAR, materialConvert);

				//Shininess
				glMaterialf(GL_FRONT, GL_SHININESS, material.GetShininess());

				lastMatIndex = _materialIds[i*3];
			}
		}
		else {
			if (_materialIds[i*3] != lastMatIndex) {
				// Set Colour if no lighting
				glm::vec3 finalColour = glm::normalize(material.GetAmbient() + material.GetDiffuse());
				glColor3f(finalColour.r, finalColour.g, finalColour.b);
				lastMatIndex = _materialIds[i*3];
			}
		}
		
		// Calculate Normal
		glm::vec3 u = pointB - pointA;
		glm::vec3 v = pointC - pointA;

		glm::vec3 finalNormal = glm::normalize(glm::vec3((u.y * v.z) - (u.z * v.y),
			(u.z * v.x) - (u.x * v.z),
			(u.x * v.y) - (u.y * v.x)));

		glNormal3f(finalNormal.x, finalNormal.y, finalNormal.z);

		// Draw Vertex
		glVertex3f(
			pointA.x,
			pointA.y,
			pointA.z);
		glVertex3f(
			pointB.x,
			pointB.y,
			pointB.z);
		glVertex3f(
			pointC.x,
			pointC.y,
			pointC.z);
	}
	glEnd();

	glPopMatrix();
}

void Scene1::Update(unsigned int td_milli)
{
}
