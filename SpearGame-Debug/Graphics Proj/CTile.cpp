#include "CTile.h"

void CTile::Initalise(CCamera * newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint tex)
{
	CQuad::Initalise(newCamera, sizeH, sizeW, initalX, initalY, prog, tex);

	boxCollider.initalise(-0.5, 0.5, 0.5, -0.5, getRefToModel());
}
