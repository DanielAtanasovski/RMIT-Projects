#include "CollidableEntity.h"
#include "../math/Math.h"
#include <math.h>

#if _WIN32
#   include <Windows.h>
#endif
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

void CollidableEntity::drawDebugCollisionCircle()
{
	glColor3f(DEBUG_COLOUR.x, DEBUG_COLOUR.y, DEBUG_COLOUR.z);
	glBegin(GL_LINE_LOOP);
	for (size_t i = 0; i < DEBUG_CIRCLE_MAX_STEPS; i++)
	{
		float step = i / (float)DEBUG_CIRCLE_MAX_STEPS * 2 * M_PI;
		float x = collisionRadius * cosf(step);
		float y = collisionRadius * sinf(step);
		glVertex3f(x, y, 0.0f);
	}
	glEnd();
}
