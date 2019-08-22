#include "Button.h"

CButton::CButton(std::string text)
{
	currentStr = text;
	label = new TextLabel(text, "Resources/Fonts/arial.ttf", glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
	label->Render();
	offset = glm::vec2(label->getTextWidth()*0.5, 5);
}

CButton::~CButton()
{
	delete label;
	label = 0;
}

void CButton::Initalise(CCamera * newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint tex)
{
	CQuad::Initalise(newCamera, sizeH, sizeW, initalX, initalY, prog, tex);
	label->SetPosition(this->getPos() - offset);
}

void CButton::render()
{
	CQuad::render(glm::mat4());
	label->Render();
}

void CButton::setText(std::string str)
{
	currentStr = str;
	label->SetText(str);
	offset = glm::vec2((str.size()*0.5) * 10, 5);
	label->SetPosition(this->getPos() - offset);
}

bool CButton::click(glm::vec2 mousePos)
{
	glm::vec2 pos = getPos();
	glm::vec2 scale = getScale();
	if (mousePos.x > pos.x - (scale.x*0.5f) && mousePos.x < pos.x + (scale.x*0.5f) && mousePos.y < pos.y + (scale.y*0.5f) && mousePos.y > pos.y - (scale.y*0.5f))
	{
		return true;
	}
	return false;
}
