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

	int gridWidth = glutGet(GLUT_SCREEN_WIDTH)/60;
	int gridHeight = glutGet(GLUT_SCREEN_HEIGHT)/60;

	std::vector<std::vector<int>> tileInts = std::vector<std::vector<int>>(gridWidth);
	for (auto& vec : tileInts) {
		vec = std::vector<int>(gridHeight);
	}

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
				tileInts[x][y] = item == '1' ? 1 : 0;
			}
			x++;
		}
		y++;
		x = 0;
	}
	file.close();

	b2BodyDef def;
	def.type = b2_staticBody;
	def.position = b2Vec2(0.0f, 0.0f);

	b2Body* body = world->CreateBody(&def);
	this->body = body;
	for (x = 0; x < gridWidth; x++) {
		for (y = 0; y < gridHeight; y++) {
			if (tileInts[x][y] == 1) {
				int xOffset = 0;
				int yOffset = 0;
				for (xOffset = 0; x + xOffset < gridWidth; xOffset++) {
					if (tileInts[x + xOffset][y] != 1) {
						continue;
					}
				}
				bool foundBottomValue = false;
				for (yOffset = 0; y + yOffset < gridHeight; yOffset++) {
					for (int xOff = 0; xOff <= xOffset; xOff++) {
						if (tileInts[x + xOff][y + yOffset] != 1) {
							yOffset--;
							foundBottomValue = true;
							break;
						}
					}
					if (foundBottomValue) break;
				}
				b2PolygonShape box;
				box.SetAsBox((xOffset + 1) * size, (yOffset + 1) * size, b2Vec2(x * size, y * size), 0.0f);

				b2FixtureDef fix;
				fix.shape = &box;
				fix.density = 1.0f;
				fix.friction = 0.3f;
				fix.filter.categoryBits = PLATFORM_CATEGORY;
				fix.filter.maskBits = PLAYER_CATEGORY | SPEAR_CATEGORY;
				body->CreateFixture(&fix);

				for (int xDiff = 0; xDiff <= xOffset; xDiff++){
					for (int yDiff = 0; yDiff <= yOffset; yDiff++) {
						tileInts[x + xDiff][y + yDiff] == 2;
						(y == 0 || tileInts[x + xDiff][y + yDiff - 1] == 0) ? topTiles.push_back(glm::vec2(x + xDiff, y + yDiff)) : undergroundTiles.push_back(glm::vec2(x + xDiff, y + yDiff));
					}
				}
			}
		}
	}

	/*CTile* temp = new CTile();
	temp->Initalise(camera, size, size, -(x * size + size / 2.0f - B2_WIDTH / 2.0f), -(y * size + size / 2.0f - B2_HEIGHT / 2.0f), prog, TextureLoader::get("ground"), world);
	tileArray.push_back(temp);
	*/
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
