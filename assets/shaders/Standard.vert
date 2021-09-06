#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTexCoords;

uniform mat4 perspectiveMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec3 Normal;
out vec3 FragPos;

void main()
{
	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0f);
	Normal = aNormal;
	FragPos = vec3(modelMatrix * vec4(aPos, 1.0f));
}