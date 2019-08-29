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

void CPlayer::update(float deltaTime, std::vector<CTile*> & level)
{
	bool up, down, left, right, shoot, punch;

	punch = gameInput->checkKeyDownFirst(KEY, GLFW_KEY_Q);
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
		punch = gpState.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] > -1;
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

	while (getPos().y < -0.5f * static_cast<float>(Utils::SCR_HEIGHT)) {
		translate(Y, static_cast<float>(Utils::SCR_HEIGHT), true);
	}

	float hFriction = grounded ? 4.0f : 0.1f;
	float vFriction = 1.0f;

	float hRatio = 1.0f / (1 + deltaTime * hFriction);
	float vRatio = 1.0f / (1 + deltaTime * vFriction);

	velocity.x *= hRatio;
	velocity.y *= vRatio;

	if (velocity != glm::vec2(0.0f, 0.0f))
	{

		float moveMax = velocity.length() * deltaTime;
		float moveCount = 0.0f;
		glm::vec2 step = velocity * deltaTime;
		if (moveMax > 1.0f) {
			step = glm::normalize(velocity);
		}

		while (moveCount < moveMax) {
			bool breaking = false;
			translate(X, step.x, true);
			translate(Y, step.y, true);
			for (CTile *tile : level) {
				if (tile->GetCollider().collide(collider)) {
					translate(X, -step.x, true);
					translate(Y, -step.y, true);
					breaking = true;
					grounded = true;
					break;
				}
			}
			if (breaking) break;
			moveCount += fmin(moveMax + 0.01f, 1.0f);
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
		if (collider.collide(spear->getCollider()) && spear->isInWall() && punch)
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
