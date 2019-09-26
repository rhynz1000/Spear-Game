#ifndef __HELP_H__
#define __HELP_H__

#include "glew.h"
#include "freeglut.h"
#include "SOIL.h"

#include "ShaderLoader.h"
#include "Selector.h"

#include <iostream>
#include <conio.h>
#include <cmath>
#include <math.h>

class HMenu
{
public:
	HMenu();
	~HMenu();

	void Display();
	void SetOpen();
	void RenderHM();

private:
	bool open;
	GLuint ProgramHM;
	GLuint vboHM;
	GLuint vaoHM;
	GLuint eboHM;
	GLuint textureHM;

	ShaderLoader shaderloaderHM;

	GLfloat verticesHM;
	GLuint indicesHM;

#define KEY_LEFT 75

};

#endif //__HELP_H__