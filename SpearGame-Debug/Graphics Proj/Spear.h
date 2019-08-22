#pragma once
#include "Utils.h"
#include "Quad.h"
class CSpear :
	public CQuad
{
public:
	CSpear(glm::vec2 initVel) { velocity = initVel; }
	~CSpear() {}

	void update(float deltaTime);

private:
	glm::vec2 velocity;
};

