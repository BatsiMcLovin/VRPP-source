
#ifndef HEIGHTFIELDSCENE_H_
#define HEIGHTFIELDSCENE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application/ApplicationStates.h"
#include "PlaceHolderListeners.h"

namespace HeightfieldScene{

	//VOs
	VirtualObject* terrain;
	VirtualObject* test;

	//FBOs
	FrameBufferObject* fboGround;
	FrameBufferObject* fboNormals;
	FrameBufferObject* fboGloss;

	GLuint fboTexture;

	//Camera
	Camera* camera;

	//Tesxtures
	Texture* ground1;
	Texture* ground2;
	Texture* mask;

	Texture* normals1;	//normalmaps
	Texture* normals2;

	Texture* specular1;	//glossmaps
	Texture* specular2;

	static void createScene(ApplicationState* state){

		//VOs
		//terrain = state->createVirtualObject(RESOURCES_PATH"/Heightfield/terrainTest.obj",VirtualObjectFactory::TERRAIN);
		test = state->createVirtualObject(RESOURCES_PATH "/demo_scene/demo_scene_ground.dae", VirtualObjectFactory::OTHER, 0.0f, 1, true);

		//FBOs
		fboGround = new FrameBufferObject(800,600);
		fboGround->bindFBO();
		fboGround->createPositionTexture();
		/*
		glGenTextures(1,&fboTexture);
		glBindTexture(GL_TEXTURE_2D,fboTexture);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA16F,800,600,0,GL_RGBA,GL_FLOAT,0);
		 */
		fboGround->makeDrawBuffers();
		fboGround->unbindFBO();

		//Textures
		ground1 = new Texture(RESOURCES_PATH"/Heightfield/seamlessSandTest.jpg");
		ground2 = new Texture(RESOURCES_PATH"/Heightfield/seamlessStonesTest.jpg");
		mask = new Texture(RESOURCES_PATH"/Heightfield/terrainTest.png");

		normals1 = new Texture(RESOURCES_PATH"/Heightfield/seamlessSandTestNormal.jpg");	//normalmaps
		normals2 = new Texture(RESOURCES_PATH"/Heightfield/seamlessStonesTestNormal.jpg");

		specular1 = new Texture(RESOURCES_PATH"/Heightfield/seamlessSandTestSpecular.jpg");	//glossmaps
		specular2 = new Texture(RESOURCES_PATH"/Heightfield/seamlessStonesTestSpecular.jpg");

		//Camera

	}

	static void configInputHandling(ApplicationState* state){

		IOHandler* io = state->getIOHandler();
	}
}


#endif /* HEIGHTFIELDSCENE_H_ */
