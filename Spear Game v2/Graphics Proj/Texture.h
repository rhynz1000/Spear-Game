#pragma once

// Dependency Includes
#include <glew.h>

#include <map>

// Library Includes
#include <iostream>
#include <filesystem>

class TextureLoader
{
public:
	TextureLoader(void);
	~TextureLoader(void);
	static void Initialise(std::string textureFolder);
	static GLuint get(std::string textureName);
private:
	static std::map<std::string, GLuint> textures;
	static GLuint CreateTexture(const char* TextureFilename);//creates a texture from a filename
};