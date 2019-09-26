#include "CLevel.h"



CLevel::CLevel()
{
}


CLevel::~CLevel()
{
	for (CTile *tile : tileArray) {
		delete tile;
	}
}

void CLevel::LoadFromCSV(std::string filePath, CCamera * camera, GLuint prog)
{
	const float size = 60.0f;
	GLuint tex = TextureLoader::CreateTexture("Resources/Textures/Rayman.jpg");
	std::ifstream file;
	file.open(filePath);
	if (!file.good()) return;
	int x{ 0 }, y{ 0 };
	while (!file.eof()) {
		std::string line;
		std::getline(file, line);
		for (char item : line) {
			if (item == ',') continue;
			if (item == '1') {
				CTile* temp = new CTile();
				temp->Initalise(camera, size, size, -(x * size + size / 2.0f - Utils::SCR_WIDTH / 2.0f), -(y * size + size / 2.0f - Utils::SCR_HEIGHT / 2.0f), prog, tex);
				tileArray.push_back(temp);
			}
			x++;
		}
		y++;
		x = 0;
	}
	file.close();
}

void CLevel::Render()
{
	for (CTile *tile : tileArray) {
		tile->render(glm::mat4());
	}
}

std::vector<CTile*>& CLevel::GetTiles()
{
	return tileArray;
}
