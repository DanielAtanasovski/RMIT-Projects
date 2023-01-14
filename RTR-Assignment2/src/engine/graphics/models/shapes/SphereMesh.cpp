#include "SphereMesh.h"
#define _USE_MATH_DEFINES
#include <math.h>
// With help from http://www.songho.ca/opengl/gl_sphere.html

SphereMesh::SphereMesh(float radius, int sectors, int stacks)
{
	_radius = radius;
	_stacks = stacks;
	_sectors = sectors;
	CalculateSphereMesh();
	SetupMesh();
}

SphereMesh::SphereMesh(float radius)
{
    _radius = radius;
    _stacks = MIN_STACK_COUNT;
    _sectors = MIN_SECTOR_COUNT;
    CalculateSphereMesh();
    SetupMesh();
}

void SphereMesh::Recalculate(glm::vec3 scale)
{
}

void SphereMesh::CalculateSphereMesh()
{
	float x, y, z, xy; // vertexes
	float nx, ny, nz, lengthInv = 1.0f / _radius; // normal
	float s, t; // tex coords

	float sectorStep = 2 * M_PI / _sectors;
	float stackStep = M_PI / _stacks;
	float sectorAngle, stackAngle;

    _vertices.clear();
    _indices.clear();
    
    // Vertex Data
    for (int i = 0; i <= _stacks; ++i)
    {
        stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = _radius * cosf(stackAngle);             // r * cos(u)
        z = _radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= _sectors; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            glm::vec3 vec = glm::vec3(x, y, z);

            // normalized vertex normal
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            glm::vec3 norm = glm::vec3(nx, ny, nz);

            // vertex tex coord between [0, 1]
            s = (float)j / _sectors;
            t = (float)i / _stacks;
            glm::vec2 tex = glm::vec2(s, t);

            _vertices.push_back({ vec, norm, tex });
        }
    }
	
    // Indices
    unsigned int k1, k2;
    for (int i = 0; i < _stacks; ++i)
    {
        k1 = i * (_sectors + 1);     // beginning of current stack
        k2 = k1 + _sectors + 1;      // beginning of next stack

        for (int j = 0; j < _sectors; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if (i != 0)
            {
                // k1---k2---k1+1
                _indices.push_back(k1);
                _indices.push_back(k2);
                _indices.push_back(k1 + 1);
            }

            if (i != (_stacks - 1))
            {
                // k1+1---k2---k2+1
                _indices.push_back(k1 + 1);
                _indices.push_back(k2);
                _indices.push_back(k2 + 1);
            }
        }
    }
}
