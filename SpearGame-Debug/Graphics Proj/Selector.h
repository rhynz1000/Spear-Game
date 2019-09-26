#ifndef __SELECTOR_H__
#define __SELECTOR_H__

#include "glew.h"
#include "freeglut.h"
#include "SOIL.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "ShaderLoader.h"

class CSelector
{
public:
	CSelector();
	~CSelector();

	void RenderCS(int option);

private:
	GLuint ProgramCS;
	GLuint vboCS;
	GLuint vaoCS;
	GLuint eboCS;
	GLuint textureCS;

	ShaderLoader shaderloaderCS;

	GLfloat verticesCS;
	GLuint indicesCS;
};

#endif
