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
	C2DCollider getCollider() { return collider; }
	CSpear* getSpear() { return spear; }
	CSpear* swapSpear(CSpear* spear);

private:
	CSpear* spear = 0;
	CInput* gameInput;
	CCamera* camera;
	GLuint spearProg, spearTex;
	float speed = 400.0f;
	float spearSpd = 1000.0f;
	glm::vec2 velocity;
	bool grounded = false;
	bool canDoubleJump = true;
	int joystick = 0;
	C2DCollider collider;

};