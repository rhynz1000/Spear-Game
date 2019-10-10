#include "Circle.h"



CCircle::CCircle()
{
}


CCircle::~CCircle()
{
}

//initalises with physics body
void CCircle::Initalise(CCamera * newCamera, float diameter, float initalX, float initalY, GLuint prog, GLuint tex, b2World * world, b2BodyType type, uint16 categoryBits, uint16 maskBits)
{
	Initalise(newCamera, diameter, initalX, initalY, prog, tex);

	b2BodyDef def;
	def.type = type;
	def.position = b2Vec2(initalX, initalY);

	b2Body * body = world->CreateBody(&def);

	b2CircleShape circle;
	circle.m_radius = diameter /2;

	b2FixtureDef fix;
	fix.shape = &circle;
	fix.density = 1.0f;
	fix.friction = 0.3f;

	body->CreateFixture(&fix);

	this->body = body;
	//this->setBody(body);
}

//initalises without physics body
void CCircle::Initalise(CCamera * newCamera, float diameter, float initalX, float initalY, GLuint prog, GLuint tex)
{
	float radius = 0.5f;

	const int sections = 50;
	const int vertexAttrib = 5;
	const int indexPerTri = 3;
	const int indexPerLine = 2;
	const double M_PI = 3.14159;

	double theta = 0;

	float vertices[(sections)* vertexAttrib];
	int offset = 0;

	for (int j = 0; j < sections; j++)
	{
		float x = (float)sin(theta)* radius;
		float y = (float)cos(theta)* radius;
		float z = 0;

		vertices[offset++] = x;
		vertices[offset++] = y;
		vertices[offset++] = z;

		vertices[offset++] = (float)((x / radius + 1)*0.5);
		vertices[offset++] = (float)((-y / radius + 1)*0.5);

		theta += (2 * M_PI / (sections - 1));
	}
	//construcing indices array
	GLuint indices[(sections)* indexPerTri];
	offset = 0;
	for (int i = 0; i < sections - 2; i++)
	{
		indices[offset++] = 0;
		indices[offset++] = sections - (i + 1);
		indices[offset++] = sections - (i + 2);
	}

	//initalizing sphere with shapes arrays
	C2DShape::Initalise(newCamera, diameter, diameter, initalX, initalY, prog, tex, vertices, indices, sizeof(vertices), sizeof(indices));

	setIndiceCount(sizeof(indices) / sizeof(GLuint));
}
