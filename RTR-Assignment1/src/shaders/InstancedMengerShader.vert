#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aInstanceModelMatrixA;
layout (location = 2) in vec4 aInstanceModelMatrixB;
layout (location = 3) in vec4 aInstanceModelMatrixC;
layout (location = 4) in vec4 aInstanceModelMatrixD;

out vec3 FragPos;

out mat4 modelMatrix;

void main()
{
	modelMatrix = mat4(aInstanceModelMatrixA, aInstanceModelMatrixB, aInstanceModelMatrixC, aInstanceModelMatrixD);
	FragPos = vec3(modelMatrix * vec4(aPos, 1.0f));
	gl_Position = vec4(aPos, 1.0);
}