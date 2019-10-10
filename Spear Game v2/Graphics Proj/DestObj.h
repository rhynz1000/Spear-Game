#pragma once
#include "2DShape.h"
class CDestObj :
	public C2DShape
{
public:
	CDestObj(C2DShape shape):C2DShape(shape) {}
	~CDestObj() {}
	void SetHealth(float newHealth) { health = newHealth; maxHealth = newHealth; startRed = this->getColour().x; }
	void RemoveHealth(float damage) { health -= damage; }
	void ResetHealth() { health = maxHealth; }
	float GetHealth() { return health; }
	void updateColour() { glm::vec4 colour = this->getColour(); colour.x = lerp(1.0f, startRed, health / maxHealth); this->setColour(colour); }
	float lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

private:
	float health = 0;
	float maxHealth = 0;
	float startRed = 0;
};

