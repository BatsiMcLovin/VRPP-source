/*
 * FrameBufferObject.h
 *
 *  Created on: 21.01.2014
 *      Author: Dr.M
 */

#ifndef FRAMEBUFFEROBJECT_H_
#define FRAMEBUFFEROBJECT_H_

#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class FrameBufferObject {
public:
	FrameBufferObject(int width=800, int height=800);
	virtual ~FrameBufferObject();

	void createPositionTexture();
	void createNormalTexture();
	void createColorTexture();
	void createSpecularTexture();
	void createShadowMap();
	void createDepthBuffer();

	GLuint getFboHandle();
	GLuint getPositionTextureHandle();
	GLuint getNormalTextureHandle();
	GLuint getColorTextureHandle();
	GLuint getSpecularTextureHandle();
	GLuint getShadowMapHandle();
	GLuint getDepthBufferHandle();


	void bindFBO();
	void unbindFBO();
	void bindPositionTexture();
	void bindNormalTexture();
	void bindColorTexture();
	void bindSpecularTexture();
	void bindShadowMap();
	void bindDepthBuffer();
	void unbindTexture();
	void unbindAllTextures();
	void makeDrawBuffers();
	void resize(int width, int height);

	GLfloat getWidth();
	GLfloat getHeight();


protected:

	int mHeight, mWidth;

    GLuint mFramebufferHandle;

    GLuint mPositionTextureHandle;
    GLuint mNormalTextureHandle;
    GLuint mColorTextureHandle;
    GLuint mSpecularTextureHandle;
    GLuint mShadowMapHandle;
    GLuint mDepthbufferHandle;

    std::vector <GLenum> mDrawBuffers;

};

#endif /* FRAMEBUFFEROBJECT_H_ */
