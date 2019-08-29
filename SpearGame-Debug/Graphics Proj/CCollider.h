#pragma once

#include "Utils.h"
class C2DCollider
{
public:
	C2DCollider() {}
	~C2DCollider() {}

	void initalise(float leftSide, float rightSide, float topSide, float bottomSide, glm::mat4* parentModel);
	bool collide(C2DCollider other);

	float left, right, top, bottom;
	glm::mat4 *model;

private:
	float pointToLine(glm::vec2 point, glm::vec2 lineA, glm::vec2 lineB);
};

