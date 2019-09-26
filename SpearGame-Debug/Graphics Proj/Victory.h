#ifndef __VICTORY_H__
#define __VICTORY_H__

#include "glew.h"
#include "freeglut.h"
#include "SOIL.h"

#include "ShaderLoader.h"
#include "Selector.h"

#include <iostream>
#include <conio.h>
#include <cmath>
#include <math.h>

class EMenu
{
public:
	EMenu();
	~EMenu();

	void RenderEM();

private:
	bool open;
	GLuint ProgramEM;
	GLuint vboEM;
	GLuint vaoEM;
	GLuint eboEM;
	GLuint textureEM;

	ShaderLoader shaderloaderEM;

	GLfloat verticesEM;
	GLuint indicesEM;

#define KEY_LEFT 75

};

#endif //__VICTORY_H__