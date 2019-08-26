#include "Player.h"

void CPlayer::initalise(CInput * input, CCamera* newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint playerTex, int joy, GLuint initSpearTex)
{
	CQuad::Initalise(newCamera, sizeH, sizeW, initalX, initalY, prog, playerTex);

	spearProg = prog;
	spearTex = initSpearTex;
	gameInput = input;
	camera = newCamera;
	joystick = joy;

	collider.initalise(-0.5, 0.5, 0.5, -0.5, this->getRefToModel());
}

void CPlayer::update(float deltaTime)
{
	bool up, down, left, right, shoot;
	shoot = gameInput->checkKeyDownFirst(KEY, GLFW_KEY_E);
	up = gameInput->checkKeyDownFirst(KEY, GLFW_KEY_SPACE);
	left = gameInput->checkKeyDown(KEY, GLFW_KEY_A);
	right = gameInput->checkKeyDown(KEY, GLFW_KEY_D);
	float horizontalSpeed = (left && !right) || (right && !left) ? (right ? 1.0f : -1.0f) : 0.0f;
	glm::vec2 spearDir = glm::vec2(0.5f, 0.5f);
	
	float halfScrWidth = ((float)Utils::SCR_WIDTH) / 2;
	float halfScrHeight = ((float)Utils::SCR_HEIGHT) / 2;

	if (gameInput->isJoystickValid(joystick))
	{
		GLFWgamepadstate gpState = gameInput->getJoystickInput(joystick);
		shoot = gpState.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] > -1;
		up = gpState.buttons[GLFW_GAMEPAD_BUTTON_A];
		horizontalSpeed = gpState.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
		horizontalSpeed = (abs(horizontalSpeed) > 0.2f) ? horizontalSpeed : 0.0f;
		spearDir = glm::normalize(glm::vec2(gpState.axes[GLFW_GAMEPAD_AXIS_RIGHT_X], -gpState.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]));
	}

	if (horizontalSpeed != 0.0f) {
		velocity = glm::vec2(velocity.x + horizontalSpeed * deltaTime * speed * (grounded ? 5.0f : 1.0f), velocity.y);
		if (velocity.x < 0) {
			velocity.x = fmaxf(velocity.x, horizontalSpeed * speed);
		}
		else {
			velocity.x = fminf(velocity.x, horizontalSpeed * speed);
		}
	}

	if (up && grounded ) {
		velocity.y += 800.0f;
	}
	else if(up && canDoubleJump && velocity.y < 400.0f) {
		velocity.y = 800.0f;
		canDoubleJump = false;
	}

	velocity = velocity + glm::vec2(0.0f, -1500.0f * deltaTime);

	while (getPos().x < -0.5f * static_cast<float>(Utils::SCR_WIDTH)) {
		translate(X, static_cast<float>(Utils::SCR_WIDTH), true);
	}
	while (getPos().x > 0.5f * static_cast<float>(Utils::SCR_WIDTH)) {
		translate(X, -static_cast<float>(Utils::SCR_WIDTH), true);
	}

	while (getPos().y > 0.5f * static_cast<float>(Utils::SCR_HEIGHT)) {
		translate(Y, -static_cast<float>(Utils::SCR_HEIGHT), true);
	}

	float hFriction = grounded ? 4.0f : 0.1f;
	float vFriction = 1.0f;

	float hRatio = 1.0f / (1 + deltaTime * hFriction);
	float vRatio = 1.0f / (1 + deltaTime * vFriction);

	velocity.x *= hRatio;
	velocity.y *= vRatio;

	if (velocity != glm::vec2(0.0f, 0.0f))
	{
		translate(X, velocity.x * deltaTime, true);
		if (getPos().y + velocity.y * deltaTime < -0.5f * static_cast<float>(Utils::SCR_HEIGHT)) {
			translate(Y, -0.5f * static_cast<float>(Utils::SCR_HEIGHT), false);
			velocity.y = 0.0f;
			grounded = true;
			canDoubleJump = true;
		}
		else {
			translate(Y, velocity.y * deltaTime, true);
			grounded = false;
		}
	}

	if (shoot && spear == 0)
	{
		spear = new CSpear(spearDir*spearSpd + velocity);
		spear->Initalise(camera, 10,50, getPos().x, getPos().y, spearProg, spearTex);
	}

	if (spear != 0)
	{
		glm::vec2 tipPos = glm::vec2(spear->getScale().x / 2, 0);
		tipPos = glm::vec2(spear->getRotationMat() * glm::vec4(tipPos, 0.0f, 1.0f));
		tipPos += spear->getPos();

		if (tipPos.y < -0.5f * static_cast<float>(Utils::SCR_HEIGHT) || tipPos.x < -0.5f * static_cast<float>(Utils::SCR_WIDTH) || tipPos.x > 0.5f * static_cast<float>(Utils::SCR_WIDTH))
		{
			spear->setInWall(true);
		}
		spear->update(deltaTime);
		if (collider.collide(spear->getCollider()) && spear->isInWall())
		{
			delete spear;
			spear = 0;
		}
	}
}

void CPlayer::render()
{
	C2DShape::render(glm::mat4());
	if (spear != 0)
	{
		spear->render(glm::mat4());
	}
}
