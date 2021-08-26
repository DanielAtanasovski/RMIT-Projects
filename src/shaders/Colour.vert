#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in int aMaterialID;

uniform mat4 viewMatrix;
uniform mat4 perspectiveMatrix;

flat out int MaterialID;

void main()
{
	gl_Position = perspectiveMatrix * viewMatrix * vec4(aPos, 1.0);
	MaterialID = aMaterialID;
}