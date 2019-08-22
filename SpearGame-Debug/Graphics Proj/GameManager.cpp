#include "GameManager.h"

GLuint program, program1;

GLuint texture, texture1;

void CGameManager::initalise(CInput* input)
{
	GameInput = input;
	program = ShaderLoader::CreateProgram("Resources/Shaders/Basic.ver", "Resources/Shaders/Basic.frag");
	program1 = ShaderLoader::CreateProgram("Resources/Shaders/Basic.ver", "Resources/Shaders/Colour.frag");

	texture = TextureLoader::CreateTexture("Resources/Textures/Rayman.jpg");
	texture1 = TextureLoader::CreateTexture("Resources/Textures/AwesomeFace.png");

	camera.orthoInti(Utils::SCR_WIDTH, Utils::SCR_HEIGHT, 0.1f, 100.0f);

	player.initalise(GameInput, &camera, 100, 100, 0, 0, program, texture1);
}

void CGameManager::update()
{
	deltaTime = std::chrono::high_resolution_clock::now() - previousTime;
	previousTime = std::chrono::high_resolution_clock::now();

	float DT = deltaTime.count() > 1.0f ? 1.0f : deltaTime.count();
	
	player.update(DT);
}

void CGameManager::render()
{
	player.render();
}