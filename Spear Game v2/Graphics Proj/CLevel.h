#pragma once
#include "CTile.h"
class CLevel
{
public:
	CLevel();
	~CLevel();
	void LoadFromCSV(std::string filePath, CCamera * camera, GLuint prog, b2World* world);
	void Render();
private:
	std::vector<glm::vec2> topTiles, undergroundTiles;
	CQuad * topTile, * undergroundTile;
	b2Body * body;
	CQuad* background;
};

