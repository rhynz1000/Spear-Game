#include "Spear.h"


void CSpear::update(float deltaTime)
{
	velocity = velocity + glm::vec2(0.0f, -1500.0f * deltaTime);

	translate(X, velocity.x* deltaTime, true);
	translate(Y, velocity.y* deltaTime, true);
}
