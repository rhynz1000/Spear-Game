#include "CLevel.h"



CLevel::CLevel()
{
	background = new CQuad();
}


CLevel::~CLevel()
{
	for (CTile *tile : tileArray) {
		delete tile;
	}
}

void CLevel::LoadFromCSV(std::string filePath, CCamera * camera, GLuint prog, b2World* world)
{
	background->Initalise(camera, SCR_HEIGHT, SCR_WIDTH, 0.0f, 0.0f, prog, TextureLoader::get("background"));

	std::vector<CTile*>::iterator itr = tileArray.begin();
	while (tileArray.size() > 0) {
		(*itr)->destroyBody();
		delete* itr;
		itr = tileArray.erase(itr);
	}
	const float size = 60.0f / PPM;
	GLuint tex = TextureLoader::get("ground");
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
				bool underground = false;
				for (CTile* tile : tileArray) {
					if (tile->getPos().x == -(x * size + size / 2.0f - SCR_WIDTH / 2.0f) && tile->getPos().y == -((y-1) * size + size / 2.0f - SCR_HEIGHT / 2.0f)) {
						underground = true;
						break;
					}
				}
				temp->Initalise(camera, size, size, -(x * size + size / 2.0f - B2_WIDTH / 2.0f), -(y * size + size / 2.0f - B2_HEIGHT / 2.0f), prog, underground ? TextureLoader::get("ground_mid") : TextureLoader::get("ground"), world);
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
	background->render(glm::mat4());
	for (CTile *tile : tileArray) {
		tile->render(glm::mat4());
	}
}

std::vector<CTile*>& CLevel::GetTiles()
{
	return tileArray;
}
