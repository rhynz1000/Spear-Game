#pragma once

// Dependency Includes
#include <glew.h>
//#include <freeglut.h>
#include "Dependencies/GLFW/glfw3.h"

#include <map>

// Library Includes
#include <iostream>

class TextureLoader
{

public:
	TextureLoader(void);
	~TextureLoader(void);
	static GLuint CreateTexture(const char* TextureFilename);//crates a texture from a filename

private:
	//std::map<std::string, GLuint> textures;
};