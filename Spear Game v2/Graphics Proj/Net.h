#pragma once

#include "Quad.h"

class CNet
{
public:
	CNet(CCamera* newCamera);

private:
	CQuad top;
	CQuad bottom;
};