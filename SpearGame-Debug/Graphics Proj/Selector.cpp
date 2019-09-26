#include "Selector.h"

using namespace std;

CSelector::CSelector()
{
	GLfloat verticesCS[] = {
		 0.05f,  0.0, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // Top - Right
		-0.05f,  0.05, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // Top - Left
		-0.05f, -0.05, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // Bot - Left
	};

	GLuint indicesCS[] = {
		1, 3, 2
	};

	ProgramCS = shaderloaderCS.CreateProgram("Selector.vs", "Selector.fs");

	glGenVertexArrays(1, &vaoCS);
	glBindVertexArray(vaoCS);
	glGenBuffers(1, &vboCS);
	glGenBuffers(1, &eboCS);
	glGenTextures(1, &textureCS);

	glBindBuffer(GL_ARRAY_BUFFER, vboCS);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(verticesCS),
		verticesCS,
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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboCS);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indicesCS),
		indicesCS,
		GL_STATIC_DRAW);

	glBindTexture(GL_TEXTURE_2D, textureCS);

	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);

	int width, height;
	unsigned char* image = SOIL_load_image(
		"images\\Selector.png",
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

CSelector::~CSelector()
{

}

void CSelector::RenderCS(int option)
{
	glUseProgram(ProgramCS);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureCS);
	glUniform1i(glGetUniformLocation(ProgramCS, "SelTex"), 0);

	glm::vec3 objPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	if (option == 0)
	{
		objPosition = glm::vec3(-0.14f, 0.14f, 0.0f);
	}
	else if (option == 1)
	{
		objPosition = glm::vec3(-0.14f, -0.26f, 0.0f);
	}
	else
	{
		objPosition = glm::vec3(-0.14f, -0.68f, 0.0f);
	}

	glm::mat4 translate = glm::translate(glm::mat4(), objPosition);
	GLuint transformLoc = glGetUniformLocation(ProgramCS, "translate");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(translate));

	glBindVertexArray(vaoCS);
	//glDrawArrays(GL_TRIANGLES, 3, 0);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}