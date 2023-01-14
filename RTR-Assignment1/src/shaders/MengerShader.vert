#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 fragPos;

uniform mat4 modelMatrix;

void main()
{
	fragPos = vec3(modelMatrix * vec4(aPos, 1.0f));
	gl_Position = vec4(aPos, 1.0);
}