/*
 * Frustum.h
 *
 *  Created on: 25.02.2014
 *      Author: Dr.M
 */

#ifndef FRUSTUM_H_
#define FRUSTUM_H_

#include "IO/Camera.h"
#include "btBulletDynamicsCommon.h"
#include "Physics/PhysicsComponent.h"
#include "Visuals/GraphicsComponent.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

class RenderManager;

class Frustum {
public:
	Frustum();
	Frustum(Camera *cam);
	virtual ~Frustum();
	bool inFrustum(GraphicsComponent *gc);//return wheather or not a GC is (partially) inside of this frustum
	void setPerspectiveMatrix(GLfloat fovy, GLfloat aspect, GLfloat near, GLfloat far);//sets the perspective matrix
	glm::mat4 getPerspectiveMatrix();
	void updateModelMatrix();
	void setCamera(Camera *cam);

protected:

	Camera *mCam;
	btGhostObject *mFrustumVolume;
	glm::mat4 mPerspectiveMatrix;
};

#endif /* FRUSTUM_H_ */
