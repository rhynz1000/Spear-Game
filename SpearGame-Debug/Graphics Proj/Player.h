#pragma once

#include "Utils.h"
#include "Input.h"
#include "Quad.h"
#include "Spear.h"
#include "CCollider.h"
#include "CTile.h"

class CPlayer : public CQuad
{
public:
	CPlayer() {}
	~CPlayer() {}

	void initalise(CInput* input, CCamera* newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint playerTex, int joy, GLuint initSpearTex);
	void update(float deltaTime, std::vector<CTile*> & level, CPlayer &otherPlayer);
	void render();
	void hit(float damage) { health -= damage; }
	void reset();
	void resetScore() { score = 0; }
	void addPoint() { score++; }

	bool isDashReady() { return dashReady; }
	float getHealth() { return health; }
	int getScore() { return score; }
	C2DCollider getCollider() { return collider; }
	CSpear* getSpear() { return spear; }
	CSpear* swapSpear(CSpear* spear);

private:
	CSpear* spear = 0;
	CInput* gameInput;
	CCamera* camera;
	GLuint spearProg, spearTex;
	const float speed = 400.0f;
	const float spearSpd = 1000.0f;
	glm::vec2 velocity;
	bool grounded = false;
	bool canDoubleJump = true;
	int joystick = 0;
	C2DCollider collider, meleeRange;
	bool punchLast = false, shootLast = false, upLast = true, dashLast = false;
	const float dashCooldown = 3.0f;
	float dashCount = 0;
	bool dashReady = true;
	const float dashSpeed = 800.0f;
	float health = 100;
	const float maxHealth = 100;
	glm::vec2 spawnPoint;
	int score = 0;
};