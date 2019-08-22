#pragma once
#include <vector>
#include "Quad.h"

enum Scroll
{
	FLIPFLOP = 0,
	LOOP = 1,
};

class CAnimation
{
public:
	CAnimation() {}
	~CAnimation() {}
	void Initialise(const std::vector<GLuint> _frames, float _frameTime, Scroll _type);
	GLuint Update(float _deltaTime);
private:
	std::vector<GLuint> frames;
	float m_delay;
	float m_timer;
	int startFrame = 0;
	int currentFrame;
	int numFrames;

	bool flip = false;

	Scroll m_type;
};
