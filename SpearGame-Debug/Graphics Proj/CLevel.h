#pragma once
#include "CTile.h"
class CLevel
{
public:
	CLevel();
	~CLevel();
	void LoadFromCSV(std::string filePath, CCamera * camera, GLuint prog);
	void Render();
	std::vector<CTile>& GetTiles();
private:
	std::vector<CTile> tileArray;
};

