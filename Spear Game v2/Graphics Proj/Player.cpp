#include "Player.h"

void CPlayer::initalise(CInput * input, CCamera* newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint playerTex, int joy, GLuint initSpearTex, b2World* world)
{
	CQuad::Initalise(newCamera, sizeH, sizeW, initalX, initalY, prog, playerTex, world, b2_dynamicBody, PLAYER_CATEGORY, PLATFORM_CATEGORY|SPEAR_CATEGORY);

	body->SetFixedRotation(true);

	spearProg = prog;
	spearTex = initSpearTex;
	gameInput = input;
	camera = newCamera;
	joystick = joy;

	spawnPoint = glm::vec2(initalX, initalY);
}

void CPlayer::update(float deltaTime, CPlayer &otherPlayer)
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
	
	float halfScrWidth = ((float)SCR_WIDTH) / 2;
	float halfScrHeight = ((float)SCR_HEIGHT) / 2;

	body->SetLinearDamping(grounded ? 4.0f : 0.1f);

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


	body->ApplyForceToCenter(b2Vec2(horizontalSpeed *deltaTime * speed* (grounded ? 4.0f : 1.0f), 0), true);

	if (up && grounded)
	{
		CAudio::getInstance()->playSound("Jump", 0.3f);
		//body->ApplyLinearImpulseToCenter(b2Vec2(0, jumpForce * deltaTime), true);
		body->SetLinearVelocity({ body->GetLinearVelocity().x, jumpForce });
		canDoubleJump = true;
	}
	else if (up && canDoubleJump) {
		CAudio::getInstance()->playSound("Jump", 0.3f);
		//body->ApplyLinearImpulseToCenter(b2Vec2(0, jumpForce * deltaTime), true);
		body->SetLinearVelocity({ body->GetLinearVelocity().x, jumpForce });
		canDoubleJump = false;
	}

	if (dash && dashReady)
	{
		body->ApplyLinearImpulseToCenter(b2Vec2(((horizontalSpeed < 0) ? -dashSpeed : dashSpeed)*deltaTime , 0), true);
		dashReady = false;
		dashCount = 0;
	}
	else if (!dashReady)
	{
		dashCount += deltaTime;
		dashReady = (dashCount > dashCooldown);
	}

	while (body->GetPosition().x < -0.5f * static_cast<float>(B2_WIDTH)) {
		body->SetTransform(b2Vec2(body->GetPosition().x + B2_WIDTH,body->GetPosition().y), 0);
	}
	while (body->GetPosition().x > 0.5f * static_cast<float>(B2_WIDTH)) {
		body->SetTransform(b2Vec2(body->GetPosition().x - B2_WIDTH, body->GetPosition().y), 0);
	}

	while (body->GetPosition().y < -0.5f * static_cast<float>(B2_HEIGHT)) {
		body->SetTransform(b2Vec2(body->GetPosition().x, body->GetPosition().y + B2_HEIGHT), 0);
	}

	while (body->GetPosition().y > 0.5f * static_cast<float>(B2_HEIGHT)) {
		body->SetTransform(b2Vec2(body->GetPosition().x, body->GetPosition().y - B2_HEIGHT), 0);
	}

	

	
	if (shoot && spear == 0)
	{
		CAudio::getInstance()->playSound("Throw", 0.3f);
		spear = new CSpear();
		spear->Initalise(camera, getPos().x + spearDir.x, getPos().y + spearDir.y, this->getWorld(), spearDir*spearSpd);
		spear->setId(this->getId() + 3);
	}

	if (spear)
	{
		spear->physicsUpdate();

		b2Vec2 vecToOther;
		glm::vec2 vecToOther2;

		if (otherPlayer.getSpear())
		{
			vecToOther = otherPlayer.getSpear()->body->GetPosition() - body->GetPosition();
			vecToOther2 = glm::vec2{ vecToOther.x, vecToOther.y };

			if (punch && vecToOther.LengthSquared() < meleeRange*meleeRange && std::acos(glm::dot(glm::normalize(vecToOther2), glm::normalize(spearDir)))  < 3.1415926535f * 0.33333333f)
			{
				spear = otherPlayer.swapSpear(spear);
				spear->destroyBody();
				delete spear;
				spear = 0;
			}
		}

		if (spear)
		{
			vecToOther = spear->body->GetPosition() - body->GetPosition();
			vecToOther2 = glm::vec2{ vecToOther.x, vecToOther.y };

			//std::cout << vecToOther.LengthSquared() << ", " << std::acos(glm::dot(glm::normalize(vecToOther2), glm::normalize(spearDir))) << std::endl;

			if (punch && vecToOther.LengthSquared() < meleeRange*meleeRange && std::acos(glm::dot(glm::normalize(vecToOther2), glm::normalize(spearDir))) < 3.1415926535f * 0.33333333f)
			{
				spear->destroyBody();
				delete spear;
				spear = 0;
			}
		}
	}
	else
	{
		b2Vec2 vecToOther = otherPlayer.body->GetPosition() - body->GetPosition();
		glm::vec2 vecToOther2{ vecToOther.x, vecToOther.y };

		if (punch && vecToOther.LengthSquared() < meleeRange*meleeRange && std::acos(glm::dot(glm::normalize(vecToOther2), glm::normalize(spearDir))) < 3.1415926535f * 0.33333333f)
		{
			//std::cout << "hit" << std::endl;
			otherPlayer.hit(10);
		}
	}

	this->physicsUpdate();
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
	health = maxHealth;
	grounded = false;
	upLast = true;

	body->SetTransform(b2Vec2(spawnPoint.x / PPM, spawnPoint.y / PPM), 0);

	if (spear)
	{
		spear->destroyBody();
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
