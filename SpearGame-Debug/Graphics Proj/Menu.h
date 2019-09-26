#ifndef __MENU_H__
#define __MENU_H__

#include "glew.h"
#include "freeglut.h"
#include "SOIL.h"

#include "ShaderLoader.h"
#include "Selector.h"
#include "Help.h"

#include <iostream>
#include <conio.h>
#include <cmath>
#include <math.h>

class MMenu
{
public:
	MMenu();
	~MMenu();

	void Display();
	void RenderMM(int option);

private:
	int option;
	bool open;
	GLuint ProgramMM;
	GLuint vboMM;
	GLuint vaoMM;
	GLuint eboMM;
	GLuint textureMM;

	ShaderLoader shaderloaderMM;
	CSelector* MSelect;
	HMenu* HMenu1;

	GLfloat verticesMM;
	GLuint indicesMM;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

};

#endif //__MENU_H__