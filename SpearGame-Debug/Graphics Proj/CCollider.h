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

	struct Line
	{
		Line(glm::vec2 A, glm::vec2 B):pt1(A), pt2(B){}
		glm::vec2 pt1;
		glm::vec2 pt2;
		glm::vec2 dir() { return glm::normalize(pt1 - pt2); }
	};
};

