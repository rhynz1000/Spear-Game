#include <SOIL.h>
#include "Texture.h"

TextureLoader::TextureLoader(void){}
TextureLoader::~TextureLoader(void){}

std::map<const char*, GLuint> Textures;//map of prevously created textures

GLuint TextureLoader::CreateTexture(const char * TextureFilename)//makes a texture based on filename
{
	
	auto it = Textures.find(TextureFilename);

	if (it != Textures.end())
	{
		return (*it).second;
	}

	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height;
	unsigned char* image = SOIL_load_image(TextureFilename, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	Textures[TextureFilename] = texture;

	return texture;
}
