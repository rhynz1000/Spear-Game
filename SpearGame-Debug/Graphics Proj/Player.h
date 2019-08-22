#pragma once

#include "Utils.h"
#include "Input.h"
#include "Quad.h"
#include "Spear.h"

class CPlayer : public CQuad
{
public:
	CPlayer() {}
	~CPlayer() {}

	void initalise(CInput* input, CCamera* newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint tex, int joy);
	void update(float deltaTime);
	void render();

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

};