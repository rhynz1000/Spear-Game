#include "animation.h"

void CAnimation::Initialise(const std::vector<GLuint> _frames, float _frameTime, Scroll _type)
{
	frames = _frames;
	m_delay = _frameTime;
	numFrames = _frames.size();
	currentFrame = startFrame;
	m_type = _type;
	m_timer = 0;
	flip = false;
}

GLuint CAnimation::Update(float _deltaTime)
{
	m_timer += _deltaTime;

	if (m_timer > m_delay)
	{
		if (m_type == LOOP)
		{
			if (currentFrame < frames.size() - 1)
			{
				currentFrame++;
			}
			else
			{
				currentFrame = 0;
			}
		}
		else if (m_type == FLIPFLOP)
		{
			if (!flip)
			{
				currentFrame++;
			}
			else
			{
				currentFrame--;
			}

			if (currentFrame >= frames.size() - 1)
			{
				flip = true;
			}
			else if (currentFrame <= 0)
			{
				flip = false;
			}
		}
		m_timer = 0.0f;
	}
	return frames[currentFrame];
}
