#pragma once

#include "Input.h"
#include "Quad.h"
#include "CTile.h"
#include "Audio.h"
#include "Spear.h"

class CPlayer : public CQuad
{
public:
	CPlayer() {}
	~CPlayer() {}

	void initalise(CInput* input, CCamera* newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint playerTex, int joy, GLuint initSpearTex, b2World* world);
	void update(float deltaTime, std::vector<CTile*> & level, CPlayer &otherPlayer);
	void render();
	void hit(float damage) { health -= damage; CAudio::getInstance()->playSound("Hit", 0.3f); }
	void reset();
	void resetScore() { score = 0; }
	void addPoint() { score++; }

	bool isDashReady() { return dashReady; }
	float getHealth() { return health; }
	int getScore() { return score; }
	CSpear* getSpear() { return spear; }
	CSpear* swapSpear(CSpear* spear);
	void setGrounded(bool bg) { grounded = bg; }

private:
	CSpear* spear = 0;
	CInput* gameInput;
	CCamera* camera;
	GLuint spearProg, spearTex;
	const float speed = 400.0f;
	const float spearSpd = 10.0f;
	bool grounded = false;
	bool canDoubleJump = true;
	int joystick = 0;
	bool punchLast = false, shootLast = false, upLast = true, dashLast = false;
	const float dashCooldown = 3.0f;
	float dashCount = 0;
	bool dashReady = true;
	const float dashSpeed = 600.0f;
	float health = 100;
	const float maxHealth = 100;
	glm::vec2 spawnPoint;
	int score = 0;
	float jumpForce = 600.0f;
	const float meleeRange = 2.0f;
};