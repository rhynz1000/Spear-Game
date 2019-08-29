#pragma once
#include "Utils.h"
#include "Quad.h"
#include "CCollider.h"

class CSpear :
	public CQuad
{
public:
	CSpear(glm::vec2 initVel) :velocity(initVel) { collider.initalise(-0.5, 0.5, 0.5, -0.5, this->getRefToModel()); }
	~CSpear() {}

	void update(float deltaTime);
	C2DCollider getCollider() { return collider; }
	void setInWall(bool b) { inWall = b; }
	bool isInWall() { return inWall; }

private:
	glm::vec2 velocity;
	C2DCollider collider;
	bool inWall = false;
};

