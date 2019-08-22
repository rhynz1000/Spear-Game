#pragma once

#include <string>

#include "TextLabel.h"
#include "Quad.h"

class CButton : public CQuad
{
public:
	CButton(std::string text);
	~CButton();

	virtual void Initalise(CCamera* newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint tex);

	void render();
	void setText(std::string str);
	std::string getText() { return currentStr; }

	bool click(glm::vec2 mousePos);

private:
	TextLabel* label;
	glm::vec2 offset;
	std::string currentStr;
};