#pragma once

#include "Quad.h"

class CSpear : public CQuad
{
public:
	CSpear();
	~CSpear();
	void Initalise(CCamera* cam, float initalx, float initaly, b2World* world, glm::vec2 impulse);
	void physicsUpdate()override;

private:
	float dragConstant = 0.1f;
};

