#include "Player.h"

void CPlayer::initalise(CInput * input, CCamera* newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint playerTex, int joy, GLuint initSpearTex)
{
	CQuad::Initalise(newCamera, sizeH, sizeW, initalX, initalY, prog, playerTex);

	spearProg = prog;
	spearTex = initSpearTex;
	gameInput = input;
	camera = newCamera;
	joystick = joy;

	collider.initalise(-0.5, 0.5, 0.5, -0.5, this);
	meleeRange.initalise(0.0f, 1.0f, 0.5f, 0.5f, this);

	spawnPoint = glm::vec2(initalX, initalY);
}

void CPlayer::update(float deltaTime, std::vector<CTile*> & level, CPlayer &otherPlayer)
{
	bool up, left, right, shoot, punch, dash;

	punch = gameInput->checkKeyDownFirst(KEY, GLFW_KEY_Q);
	shoot = gameInput->checkKeyDownFirst(KEY, GLFW_KEY_E);
	up = gameInput->checkKeyDownFirst(KEY, GLFW_KEY_SPACE);
	left = gameInput->checkKeyDown(KEY, GLFW_KEY_A);
	right = gameInput->checkKeyDown(KEY, GLFW_KEY_D);
	dash = gameInput->checkKeyDown(KEY, GLFW_KEY_F);

	float horizontalSpeed = (left && !right) || (right && !left) ? (right ? 1.0f : -1.0f) : 0.0f;
	glm::vec2 spearDir = glm::vec2(0.5f, 0.5f);
	
	float halfScrWidth = ((float)Utils::SCR_WIDTH) / 2;
	float halfScrHeight = ((float)Utils::SCR_HEIGHT) / 2;

	if (gameInput->isJoystickValid(joystick))
	{
		GLFWgamepadstate gpState = gameInput->getJoystickInput(joystick);
		punch = gpState.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] > -1 && !punchLast;
		punchLast = gpState.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] > -1;
		shoot = gpState.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] > -1 && !shootLast;
		shootLast = gpState.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] > -1;
		up = gpState.buttons[GLFW_GAMEPAD_BUTTON_A] && !upLast;
		upLast = gpState.buttons[GLFW_GAMEPAD_BUTTON_A];
		horizontalSpeed = gpState.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
		horizontalSpeed = (abs(horizontalSpeed) > 0.5f) ? horizontalSpeed : 0.0f;
		spearDir = glm::normalize(glm::vec2(gpState.axes[GLFW_GAMEPAD_AXIS_RIGHT_X], -gpState.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]));

		dash = gpState.buttons[GLFW_GAMEPAD_BUTTON_X] && !dashLast;
		dashLast = gpState.buttons[GLFW_GAMEPAD_BUTTON_X];
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

	if (dash && dashReady)
	{
		velocity.x += (horizontalSpeed < 0) ? -dashSpeed : dashSpeed;
		dashReady = false;
		dashCount = 0;
	}
	else if (!dashReady)
	{
		dashCount += deltaTime;
		dashReady = (dashCount > dashCooldown);
	}

	if (up && !grounded)
	{
		//std::cout << "jump no ground: " << velocity.x << ", "<< velocity.y << std::endl;
	}

	if (up && grounded ) {
		CAudio::getInstance()->playSound("Jump", 0.3);
		velocity.y = 800.0f;
		canDoubleJump = true;
	}
	else if(up && canDoubleJump && velocity.y < 400.0f) {
		CAudio::getInstance()->playSound("Jump", 0.3);
		velocity.y = 800.0f;
		canDoubleJump = false;
	}



	if (!grounded) { velocity = velocity + glm::vec2(0.0f, -1500.0f * deltaTime); }

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
		bool coll = false;
		grounded = false;

		translate(X, velocity.x * deltaTime, true);
		translate(Y, velocity.y * deltaTime, true);

		for (CTile *tile : level) {
			if (collider.collide(tile->GetCollider())) {
				translate(X, -velocity.x * deltaTime, true);
				translate(Y, -velocity.y * deltaTime, true);
				coll = true;
				break;
			}
		}

		float moveMax = velocity.length() * deltaTime;
		float moveCount = 0.0f;
		glm::vec2 step = velocity * deltaTime;
		if (moveMax > 1.0f) {
			step = glm::normalize(velocity);
		}


		while (moveCount < moveMax && coll) {
			bool breaking = false;
			translate(Y, step.y, true);

			for (CTile *tile : level) {
				if (collider.collide(tile->GetCollider())) {
					translate(Y, -step.y, true);
					breaking = true;
					if (velocity.y > 0.0f) {
						velocity.y = 0.0f;
					}
					else if (velocity.y <= 0.0f) {
						velocity.y = 0.0f;
						grounded = true;
					}
				}
			}
			if (breaking) break;
			moveCount += fmin(moveMax + 0.01f, 1.0f);
		}

		moveCount = 0;

		while (moveCount < moveMax && coll) {
			bool breaking = false;
			translate(X, step.x, true);

			for (CTile *tile : level) {
				if (collider.collide(tile->GetCollider())) {
					translate(X, -step.x, true);
					breaking = true;
					velocity.x = 0.0f;
				}
			}
			if (breaking) break;
			moveCount += fmin(moveMax + 0.01f, 1.0f);
		}	
		
	}

	if (shoot && spear == 0)
	{

		CAudio::getInstance()->playSound("Throw", 0.3);
		spear = new CSpear(spearDir*spearSpd + velocity);
		spear->Initalise(camera, 30,60, getPos().x, getPos().y, spearProg, spearTex);
	}

	if (spear != 0)
	{
		glm::vec2 tipPos = glm::vec2(spear->getScale().x / 2, 0);
		tipPos = glm::vec2(spear->getRotationMat() * glm::vec4(tipPos, 0.0f, 1.0f));
		tipPos += spear->getPos();

		for (CTile *tile : level) {
			if (!spear->isInWall() && spear->getCollider().collide(tile->GetCollider())) {
				CAudio::getInstance()->playSound("SpearLand", 0.3);
				spear->setInWall(true);
				break;
			}
		}

		while (spear->getPos().x < -0.5f * static_cast<float>(Utils::SCR_WIDTH)) {
			spear->translate(X, static_cast<float>(Utils::SCR_WIDTH), true);
		}
		while (spear->getPos().x > 0.5f * static_cast<float>(Utils::SCR_WIDTH)) {
			spear->translate(X, -static_cast<float>(Utils::SCR_WIDTH), true);
		}

		while (spear->getPos().y > 0.5f * static_cast<float>(Utils::SCR_HEIGHT)) {
			spear->translate(Y, -static_cast<float>(Utils::SCR_HEIGHT), true);
		}

		while (spear->getPos().y < -0.5f * static_cast<float>(Utils::SCR_HEIGHT)) {
			spear->translate(Y, static_cast<float>(Utils::SCR_HEIGHT), true);
		}

		spear->update(deltaTime);
		if (collider.collide(spear->getCollider()) && spear->isInWall() && punch)
		{
			delete spear;
			spear = 0;
		}
		else if (otherPlayer.getSpear() != 0 && collider.collide(otherPlayer.getSpear()->getCollider()) && otherPlayer.getSpear()->isInWall() && punch)
		{
			spear = otherPlayer.swapSpear(spear);
			delete spear;
			spear = 0;
		}
	}

	if (spearDir.x < 0)
	{
		meleeRange.initalise(1.0f, 0.0f, 0.5f, 0.5f, this);
	}
	else if (spearDir.x > 0)
	{
		meleeRange.initalise(0.0f, 1.0f, 0.5f, 0.5f, this);
	}

	if (punch && meleeRange.collide(otherPlayer.getCollider()))
	{
		//std::cout << "hit" << std::endl;
		otherPlayer.hit(10);
	}

	if (otherPlayer.getSpear() != 0 && collider.collide(otherPlayer.getSpear()->getCollider()) && !otherPlayer.getSpear()->isInWall())
	{
		//std::cout << "ow" << std::endl;
		hit(100);
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

void CPlayer::reset()
{
	velocity = glm::vec2();
	health = maxHealth;
	grounded = false;
	upLast = true;

	translate(X, spawnPoint.x, false);
	translate(Y, spawnPoint.y, false);

	if (spear)
	{
		delete spear;
		spear = 0;
	}
}

CSpear * CPlayer::swapSpear(CSpear * spear)
{
	CSpear* returnSpear = this->spear;
	this->spear = spear;
	return returnSpear;
}
