#pragma once
#include "glm.hpp"

#include "2DShape.h"
class CCircle :
	public C2DShape
{
public:
	CCircle();
	~CCircle();
	//initalises with physics body
	virtual void Initalise(CCamera* newCamera, float radius, float initalX, float initalY, GLuint prog, GLuint tex, b2World* world, b2BodyType type, uint16 categoryBits, uint16 maskBits);
	//initalises without physics body
	virtual void Initalise(CCamera* newCamera, float radius, float initalX, float initalY, GLuint prog, GLuint tex);
};

