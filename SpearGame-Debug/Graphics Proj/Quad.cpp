#include "Quad.h"

void CQuad::Initalise(CCamera* newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint tex)
{
	//initalizing quad with shapes arrays
	C2DShape::Initalise(newCamera, sizeH, sizeW, initalX, initalY, prog, tex, vertices, indices, sizeof(vertices), sizeof(indices));
}