#include "Spear.h"


void CSpear::update(float deltaTime)
{
	if (!inWall)
	{
		velocity = velocity + glm::vec2(0.0f, -1500.0f * deltaTime);

		translate(X, velocity.x* deltaTime, true);
		translate(Y, velocity.y* deltaTime, true);

		glm::vec2 norm = glm::normalize(velocity);

		float angle = atan2f(norm.x, norm.y);

		rotate(Z, 90.0f - glm::degrees(angle), false);
	}
}
