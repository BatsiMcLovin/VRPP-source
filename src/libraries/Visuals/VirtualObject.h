#ifndef VIRTUALOBJECT_H
#define VIRTUALOBJECT_H
#include "Physics/PhysicsComponent.h"
#include "Visuals/GraphicsComponent.h"
#include <glm/glm.hpp>

class VirtualObject{
public:

	//TODO Model Matrix
	glm::mat4 modelMatrix;

	int id;
	PhysicsComponent physicsComponent;
	GraphicsComponent graphicsComponent;

	VirtualObject();

	void render();
	void updateModelMatrix();
};


#endif
