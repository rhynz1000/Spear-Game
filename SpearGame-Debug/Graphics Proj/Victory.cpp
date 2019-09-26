#include "Victory.h"

using namespace std;

EMenu::EMenu()
{
	GLfloat verticesEM[] = {
		 1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // Top - Right
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // Top - Left
		 1.0f, -1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, // Bot - Right
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // Bot - Left
	};

	GLuint indicesEM[] = {
		1, 0, 2,
		1, 2, 3
	};

	open = false;

	ProgramEM = shaderloaderEM.CreateProgram("Resources/Shaders/Menu.vs", "Resources/Shaders/Menu.fs");

	glGenVertexArrays(1, &vaoEM);
	glBindVertexArray(vaoEM);
	glGenBuffers(1, &vboEM);
	glGenBuffers(1, &eboEM);
	glGenTextures(1, &textureEM);

	glBindBuffer(GL_ARRAY_BUFFER, vboEM);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(verticesEM),
		verticesEM,
		GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboEM);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indicesEM),
		indicesEM,
		GL_STATIC_DRAW);

	glBindTexture(GL_TEXTURE_2D, textureEM);

	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);

	int width, height;
	unsigned char* image = SOIL_load_image(
		"Resources\\Textures\\EndMenu.png",
		&width,
		&height,
		0,
		SOIL_LOAD_RGB);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGB,
		width,
		height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		image);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

EMenu::~EMenu()
{

}

void EMenu::RenderEM()
{
	if (open == true)
	{
		glUseProgram(ProgramEM);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureEM);
		glUniform1i(glGetUniformLocation(ProgramEM, "MainTex"), 0);

		glBindVertexArray(vaoEM);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}