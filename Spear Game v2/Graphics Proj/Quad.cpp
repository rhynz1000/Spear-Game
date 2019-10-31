#include "Quad.h"

//initalises with physics body
void CQuad::Initalise(CCamera* newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint tex, b2World* world, b2BodyType type, uint16 categoryBits, uint16 maskBits)
{
	//initalizing quad with shapes arrays
	C2DShape::Initalise(newCamera, sizeH, sizeW, initalX, initalY, prog, tex, vertices, indices, sizeof(vertices), sizeof(indices));

	b2BodyDef def;
	def.type = type;
	def.position = b2Vec2(initalX, initalY);

	b2Body * body = world->CreateBody(&def);

	b2PolygonShape box;
	box.SetAsBox(sizeW / 2, sizeH / 2);

	b2FixtureDef fix;
	fix.shape = &box;
	fix.density = 1.0f;
	fix.friction = 0.3f;
	fix.filter.categoryBits = categoryBits;
	fix.filter.maskBits = maskBits;

	body->CreateFixture(&fix);

	this->body = body;
	//this->setBody(body);
	setWorld(world);
}

//initalises without physics body
void CQuad::Initalise(CCamera * newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint tex)
{
	C2DShape::Initalise(newCamera, sizeH, sizeW, initalX, initalY, prog, tex, vertices, indices, sizeof(vertices), sizeof(indices));
}

void CQuad::Initalise(CCamera * newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint tex, int Rot)
{
	C2DShape::Initalise(newCamera, sizeH, sizeW, initalX, initalY, prog, tex, vertices, indices, sizeof(vertices), sizeof(indices));
	if (Rot == 1)
	{
		C2DShape::scale(X, -10);
	}
}