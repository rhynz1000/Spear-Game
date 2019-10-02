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

		angle = glm::degrees(angle);

		float ang = angle / 45;

		ang = std::floorf(ang) * 45;
		angle = (fmod(ang, 45) < 22.5) ? 0 : 45;

		angle += ang;

		rotate(Z, 90.0f - angle, false);
	}
}
