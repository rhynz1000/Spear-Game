#include "CLevel.h"



CLevel::CLevel()
{
	background = new CQuad();
	topTile = new CQuad();
	undergroundTile = new CQuad();
}


CLevel::~CLevel()
{

}

void CLevel::LoadFromCSV(std::string filePath, CCamera * camera, GLuint prog, b2World* world)
{
	
	background->Initalise(camera, SCR_HEIGHT / PPM, SCR_WIDTH / PPM, 0.0f, 0.0f, prog, TextureLoader::get("background"));

	topTile->Initalise(camera, 60.0f / PPM, 60.0f / PPM, 0.0f, 0.0f, prog, TextureLoader::get("ground"));
	undergroundTile->Initalise(camera, 60.0f / PPM, 60.0f / PPM, 0.0f, 0.0f, prog, TextureLoader::get("ground_mid"));

	undergroundTiles.clear();
	topTiles.clear();
	if(body != nullptr) world->DestroyBody(body);
	body = nullptr;

	const float size = 60.0f / PPM;

	int gridWidth = SCR_WIDTH/60;
	int gridHeight = SCR_HEIGHT/60;

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
	def.position = b2Vec2((B2_WIDTH * 0.5f), B2_HEIGHT * 0.5f);

	b2Body* body = world->CreateBody(&def);
	body->SetUserData((void*)3);//Set registered type in box2d to a platform
	this->body = body;

	for (x = 0; x < gridWidth; x++) {
		for (y = 0; y < gridHeight; y++) {

			if (tileInts[x][y] == 1) {

				int xOffset = 0;
				int yOffset = 0;

				for (xOffset = 0; x + xOffset < gridWidth; xOffset++) {
					if (tileInts[x + xOffset][y] != 1) {
						break;
					}
				}
				xOffset--;

				bool foundBottomValue = false;
				for (yOffset = 0; y + yOffset < gridHeight; yOffset++) {
					for (int xOff = 0; xOff <= xOffset; xOff++) {
						if (tileInts[x + xOff][y + yOffset] != 1) {
							foundBottomValue = true;
							break;
						}
					}
					if (foundBottomValue) break;
				}
				yOffset--;

				b2PolygonShape box;
				box.SetAsBox((xOffset + 1) * 0.5f, (yOffset + 1) * 0.5f, b2Vec2((x + (xOffset + 1) * 0.5f) - (B2_WIDTH), -(y + (yOffset + 1) * 0.5f)), 0.0f);

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
						if (y == 0 || tileInts[x + xDiff][y + yDiff - 1] == 0) {
							topTiles.push_back(glm::vec2(x + xDiff - gridWidth*0.5f + 0.5f, -(y + yDiff - gridHeight * 0.5f + 0.5f)));
						}
						else {
							undergroundTiles.push_back(glm::vec2(x + xDiff - gridWidth * 0.5f + 0.5f, -(y + yDiff - gridHeight * 0.5f + 0.5f)));
						}
					}
				}
			}
		}
	}
}

void CLevel::Render()
{
	background->render(glm::mat4());
	for (glm::vec2 point : topTiles) {
		topTile->render(glm::translate(glm::mat4(), glm::vec3(point, 0.0f)));
	}
	for (glm::vec2 point : undergroundTiles) {
		undergroundTile->render(glm::translate(glm::mat4(), glm::vec3(point, 0.0f)));
	}
}
