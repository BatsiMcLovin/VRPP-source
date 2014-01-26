/*
 * Texture.h
 *
 *  Created on: 06.12.2013
 *      Author: Raphimulator
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <Visuals/TextureManager.h>
#include <string>



class Texture {
	//-----------------MEMBER FUNCTIONS-----------------
public:
	/** Man macht die Textur direkt mit dem Dateinamen */
	Texture(std::string filename);
	Texture();
	virtual ~Texture();
	std::string getTexName();

	/** Das Handle wird übergeben */
	GLuint getTextureHandle();
	/** Textur wird gebunden*/
	void bindTexture();
	/** Textur wird entbunden*/
	void unbindTexture();

	//-----------------MEMBER VARIABLES-----------------
protected:

	string mFilename;

	TextureManager* mTexManager;
};

#endif /* TEXTURE_H_ */
