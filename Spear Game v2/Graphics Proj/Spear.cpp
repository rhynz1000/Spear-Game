#include "Spear.h"



CSpear::CSpear()
{
}


CSpear::~CSpear()
{
}

void CSpear::Initalise(CCamera * cam, float initalx, float initaly, b2World * world, glm::vec2 impulse)
{
	CQuad::Initalise(cam, 30.0f / PPM, 60.0f / PPM, initalx, initaly, ShaderLoader::CreateProgram("Resources/Shaders/Basic.ver", "Resources/Shaders/Basic.frag"), TextureLoader::get("spear"), world, b2_dynamicBody, SPEAR_CATEGORY, PLATFORM_CATEGORY|PLAYER_CATEGORY);
	
	//b2CircleShape spearHead;
	//spearHead.m_radius = 15.0f / PPM;
	//spearHead.m_p = b2Vec2(15.0f / PPM, 0);

	//b2FixtureDef fix;
	//fix.shape = &spearHead;
	//fix.density = 5.0f;
	//fix.filter.categoryBits = 0b0;
	//fix.filter.maskBits = 0b0;

	//body->CreateFixture(&fix);
	setId(4);
	//body->GetFixtureList()[0].SetSensor(true);

	glm::vec2 norm = glm::normalize(impulse);

	float angle = atan2f(norm.x, norm.y);

	body->SetTransform(body->GetPosition(), (3.14159f/2.0f) - angle);

	body->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), true);
}

void CSpear::physicsUpdate()
{
	b2Vec2 vel = body->GetLinearVelocity();
	if (vel.LengthSquared() > 1)
	{
		float angle = atan2f(vel.x, vel.y);

		body->SetTransform(body->GetPosition(), (3.14159f / 2.0f) - angle);
	}

	while (body->GetPosition().x < -0.5f * static_cast<float>(B2_WIDTH)) {
		body->SetTransform(b2Vec2(body->GetPosition().x + B2_WIDTH, body->GetPosition().y), body->GetAngle());
	}
	while (body->GetPosition().x > 0.5f * static_cast<float>(B2_WIDTH)) {
		body->SetTransform(b2Vec2(body->GetPosition().x - B2_WIDTH, body->GetPosition().y), body->GetAngle());
	}

	while (body->GetPosition().y < -0.5f * static_cast<float>(B2_HEIGHT)) {
		body->SetTransform(b2Vec2(body->GetPosition().x, body->GetPosition().y + B2_HEIGHT), body->GetAngle());
	}

	while (body->GetPosition().y > 0.5f * static_cast<float>(B2_HEIGHT)) {
		body->SetTransform(b2Vec2(body->GetPosition().x, body->GetPosition().y - B2_HEIGHT), body->GetAngle());
	}

	CQuad::physicsUpdate();
}
