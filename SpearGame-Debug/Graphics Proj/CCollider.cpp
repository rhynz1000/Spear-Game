#include "CCollider.h"

void C2DCollider::initalise(float leftSide, float rightSide, float topSide, float bottomSide, glm::mat4 * parentModel)
{
	left = leftSide;
	right = rightSide;
	top = topSide;
	bottom = bottomSide;

	model = parentModel;
}

bool C2DCollider::collide(C2DCollider other)
{
	glm::vec2 topLeft, topRight, bottomLeft, bottomRight;
	glm::vec2 topLeftOther, topRightOther, bottomLeftOther, bottomRightOther;

	topLeft = glm::vec2((*model) * glm::vec4(left, top, 0.0f, 1.0f));
	topRight = glm::vec2((*model) * glm::vec4(right, top, 0.0f, 1.0f));
	bottomLeft = glm::vec2((*model) * glm::vec4(left, bottom, 0.0f, 1.0f));
	bottomRight = glm::vec2((*model) * glm::vec4(right, bottom, 0.0f, 1.0f));

	topLeftOther = glm::vec2((*other.model) * glm::vec4(other.left, other.top, 0.0f, 1.0f));
	topRightOther = glm::vec2((*other.model) * glm::vec4(other.right, other.top, 0.0f, 1.0f));
	bottomLeftOther = glm::vec2((*other.model) * glm::vec4(other.left, other.bottom, 0.0f, 1.0f));
	bottomRightOther = glm::vec2((*other.model) * glm::vec4(other.right, other.bottom, 0.0f, 1.0f));

	//first axis
	glm::vec2 lineA, lineB;
	lineA = topLeft;
	lineB = topRight;

	float max = 1, min = 0;
	float maxOther, minOther = pointToLine(topLeftOther, lineA, lineB);
	maxOther = minOther;

	float current;//= pointToLine(bottomLeft, lineA, lineB);

	//max = (current > max) ? current : max;
	//min = (current < min) ? current : min;

	//current = pointToLine(bottomRight, lineA, lineB);

	//max = (current > max) ? current : max;
	//min = (current < min) ? current : min;

	current = pointToLine(topRightOther, lineA, lineB);

	maxOther = (current > maxOther) ? current : maxOther;
	minOther = (current < minOther) ? current : minOther;

	current = pointToLine(bottomLeftOther, lineA, lineB);

	maxOther = (current > maxOther) ? current : maxOther;
	minOther = (current < minOther) ? current : minOther;

	current = pointToLine(bottomRightOther, lineA, lineB);

	maxOther = (current > maxOther) ? current : maxOther;
	minOther = (current < minOther) ? current : minOther;

	if (min > maxOther || max < minOther)
	{
		return false;
	}

	//second axis

	lineA = topLeft;
	lineB = bottomLeft;

	max = 1, min = 0;
	minOther = pointToLine(topLeftOther, lineA, lineB);
	maxOther = minOther;

	//current = pointToLine(topRight, lineA, lineB);

	//max = (current > max) ? current : max;
	//min = (current < min) ? current : min;

	//current = pointToLine(bottomRight, lineA, lineB);

	//max = (current > max) ? current : max;
	//min = (current < min) ? current : min;

	current = pointToLine(topRightOther, lineA, lineB);

	maxOther = (current > maxOther) ? current : maxOther;
	minOther = (current < minOther) ? current : minOther;

	current = pointToLine(bottomLeftOther, lineA, lineB);

	maxOther = (current > maxOther) ? current : maxOther;
	minOther = (current < minOther) ? current : minOther;

	current = pointToLine(bottomRightOther, lineA, lineB);

	maxOther = (current > maxOther) ? current : maxOther;
	minOther = (current < minOther) ? current : minOther;

	if (min > maxOther || max < minOther)
	{
		return false;
	}

	//third axis

	lineA = topLeftOther;
	lineB = topRightOther;

	max = 1, min = 0;
	minOther = pointToLine(topLeft, lineA, lineB);
	maxOther = minOther;

	//current = pointToLine(bottomLeftOther, lineA, lineB);

	//max = (current > max) ? current : max;
	//min = (current < min) ? current : min;

	//current = pointToLine(bottomRightOther, lineA, lineB);

	//max = (current > max) ? current : max;
	//min = (current < min) ? current : min;

	current = pointToLine(topRight, lineA, lineB);

	maxOther = (current > maxOther) ? current : maxOther;
	minOther = (current < minOther) ? current : minOther;

	current = pointToLine(bottomLeft, lineA, lineB);

	maxOther = (current > maxOther) ? current : maxOther;
	minOther = (current < minOther) ? current : minOther;

	current = pointToLine(bottomRight, lineA, lineB);

	maxOther = (current > maxOther) ? current : maxOther;
	minOther = (current < minOther) ? current : minOther;

	if (min > maxOther || max < minOther)
	{
		return false;
	}

	//forth axis

	lineA = topLeftOther;
	lineB = bottomLeftOther;

	max = 1, min = 0;
	minOther = pointToLine(topLeft, lineA, lineB);
	maxOther = minOther;

	//current = pointToLine(topRightOther, lineA, lineB);

	//max = (current > max) ? current : max;
	//min = (current < min) ? current : min;

	//current = pointToLine(bottomRightOther, lineA, lineB);

	//max = (current > max) ? current : max;
	//min = (current < min) ? current : min;

	current = pointToLine(topRight, lineA, lineB);

	maxOther = (current > maxOther) ? current : maxOther;
	minOther = (current < minOther) ? current : minOther;

	current = pointToLine(bottomLeft, lineA, lineB);

	maxOther = (current > maxOther) ? current : maxOther;
	minOther = (current < minOther) ? current : minOther;

	current = pointToLine(bottomRight, lineA, lineB);

	maxOther = (current > maxOther) ? current : maxOther;
	minOther = (current < minOther) ? current : minOther;

	if (min > maxOther || max < minOther)
	{
		return false;
	}

	return true;
}

float C2DCollider::pointToLine(glm::vec2 point, glm::vec2 lineA, glm::vec2 lineB)
{
	if (lineA == lineB) { return 0; }
	float u = (point.x - lineA.x)*(lineB.x - lineA.x) + (point.y - lineA.y)*(lineB.y - lineA.y);
	u /= pow(glm::length(lineB - lineA), 2);

	return u;

	/*u = (u > 1.0f) ? 1.0f : u;
	u = (u < 0.0f) ? 0.0f : u;
	closestPt = glm::vec2(lineA + u * (lineB - lineA));
	return glm::distance(closestPt, point);*/
}
