#include "CTile.h"

void CTile::Initalise(CCamera * newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint tex, b2World* world)
{
	CQuad::Initalise(newCamera, sizeH, sizeW, initalX, initalY, prog, tex, world, b2_staticBody, PLATFORM_CATEGORY, PLAYER_CATEGORY|SPEAR_CATEGORY);
	this->setId(3);
}
