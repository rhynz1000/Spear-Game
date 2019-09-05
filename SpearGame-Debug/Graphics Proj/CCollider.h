#pragma once

#include "2DShape.h"
#include "Utils.h"

enum Side
{
	None,
	Top,
	Bottom,
	Left,
	Right,
};

class C2DCollider
{
public:
	C2DCollider() {}
	~C2DCollider() {}

	void initalise(float leftSide, float rightSide, float topSide, float bottomSide, C2DShape* initParent);
	bool collide(C2DCollider other, Side &side);
	bool collide(C2DCollider other);

	float left, right, top, bottom;
	C2DShape *parent;

private:
	float pointToLine(glm::vec2 point, glm::vec2 lineA, glm::vec2 lineB);

	struct Line
	{
		Line(glm::vec2 A, glm::vec2 B) :pt1(A), pt2(B) { dir = glm::normalize(pt1 - pt2); }
		glm::vec2 pt1;
		glm::vec2 pt2;
		glm::vec2 dir;
	};
};

