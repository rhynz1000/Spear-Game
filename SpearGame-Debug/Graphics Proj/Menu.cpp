#include "Menu.h"

using namespace std;

MMenu::MMenu()
{
	option = 0;
	open = true;

	GLfloat verticesMM[] = {
		 1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // Top - Right
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // Top - Left
		 1.0f, -1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, // Bot - Right
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // Bot - Left
	};

	GLuint indicesMM[] = {
		1, 0, 2,
		1, 2, 3
	};

	ProgramMM = shaderloaderMM.CreateProgram("Resources/Shaders/Menu.vs", "Resources/Shaders/Menu.fs");
	MSelect = new CSelector;
	//HMenu1 = new HMenu;

	glGenVertexArrays(1, &vaoMM);
	glBindVertexArray(vaoMM);
	glGenBuffers(1, &vboMM);
	glGenBuffers(1, &eboMM);
	glGenTextures(1, &textureMM);

	glBindBuffer(GL_ARRAY_BUFFER, vboMM);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(verticesMM),
		verticesMM,
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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboMM);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indicesMM),
		indicesMM,
		GL_STATIC_DRAW);

	glBindTexture(GL_TEXTURE_2D, textureMM);

	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);

	int width, height;
	unsigned char* image = SOIL_load_image(
		"Resources\\Textures\\MainMenu.png",
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

MMenu::~MMenu()
{
	
}

void MMenu::Display()
{
	int c = 0;

		switch ((c = _getch())) {
		case KEY_UP:
			option = option - 1;
			cout << option << endl;
			break;

		case KEY_DOWN:
			option = option + 1;
			cout << option << endl;
			break;

		case KEY_LEFT:
			open = false;
			break;

		case KEY_RIGHT:
			if (option == 0)
			{

			}
			if (option == 1)
			{
				HMenu1->SetOpen();
			}
			else
			{
				exit;
			}
			break;
		}

		if (option > 2)
		{
			option = 0;
		}
		else if (option < 0)
		{
			option = 2;
		}

}

void MMenu::RenderMM(int option)
{
	glUseProgram(ProgramMM);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureMM);
	glUniform1i(glGetUniformLocation(ProgramMM, "MainTex"), 0);

	glBindVertexArray(vaoMM);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);

	//Display();

	MSelect->RenderCS(option);
	//HMenu1->RenderHM();
}