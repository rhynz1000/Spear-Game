#include "Help.h"

using namespace std;

HMenu::HMenu()
{
	GLfloat verticesHM[] = {
		 1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // Top - Right
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // Top - Left
		 1.0f, -1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, // Bot - Right
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // Bot - Left
	};

	GLuint indicesHM[] = {
		1, 0, 2,
		1, 2, 3
	};

	open = false;

	ProgramHM = shaderloaderHM.CreateProgram("Menu.vs", "Menu.fs");

	glGenVertexArrays(1, &vaoHM);
	glBindVertexArray(vaoHM);
	glGenBuffers(1, &vboHM);
	glGenBuffers(1, &eboHM);
	glGenTextures(1, &textureHM);

	glBindBuffer(GL_ARRAY_BUFFER, vboHM);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(verticesHM),
		verticesHM,
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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboHM);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indicesHM),
		indicesHM,
		GL_STATIC_DRAW);

	glBindTexture(GL_TEXTURE_2D, textureHM);

	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);

	int width, height;
	unsigned char* image = SOIL_load_image(
		"images\\HelpMenu.png",
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

HMenu::~HMenu()
{

}

void HMenu::Display()
{
	int c = 0;

	switch ((c = _getch())) {
	case KEY_LEFT:
		open = false;
		break;
	}

}

void HMenu::SetOpen()
{
	open = true;
}

void HMenu::RenderHM()
{
	if (open == true)
	{
	glUseProgram(ProgramHM);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureHM);
	glUniform1i(glGetUniformLocation(ProgramHM, "MainTex"), 0);

	glBindVertexArray(vaoHM);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);

	Display();
}
}