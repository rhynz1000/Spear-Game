#pragma once

#include "glm.hpp"
//#include <Box2D/Box2D.h>
#include "2DShape.h"

class CQuad : public C2DShape
{
public:
	//initalises with physics body
	virtual void Initalise(CCamera* newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint tex, b2World* world, b2BodyType type, uint16 categoryBits, uint16 maskBits);
	//initalises without physics body
	virtual void Initalise(CCamera* newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint tex);

private:

	//vertices for a quad
	GLfloat vertices[32]{

	-0.5f,  0.5f,  0.0f,	0.0f, 0.0f,
	-0.5f, -0.5f,  0.0f,	0.0f, 1.0f,
	 0.5f, -0.5f,  0.0f,	1.0f, 1.0f,
	 0.5f,  0.5f,  0.0f,	1.0f, 0.0f,
	};

	//indices for a quad
	GLuint indices[6] = {
		0, 1, 2,
		0, 2, 3,
	};
};