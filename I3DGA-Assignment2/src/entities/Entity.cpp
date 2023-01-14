#include "Entity.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Entity::Entity(Vector3 position, float rotation)
{
	this->position = position;
	this->rotation = rotation;
}
