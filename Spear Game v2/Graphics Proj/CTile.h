#pragma once
//#include "CCollider.h"
//#include <Box2D/Box2D.h>
#include "Quad.h"
class CTile :
	public CQuad
{
public:
	virtual void Initalise(CCamera* newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint tex, b2World *world);
	

	//C2DCollider GetCollider() { return boxCollider; }
private:
	//C2DCollider boxCollider;
};

