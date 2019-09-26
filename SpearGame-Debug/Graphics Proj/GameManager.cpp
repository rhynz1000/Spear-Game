#include "GameManager.h"

GLuint program, program1;

GLuint texture, texture1;

void CGameManager::initalise(CInput* input)
{
	state = 0;
	option = 0;
	GameInput = input;
	program = ShaderLoader::CreateProgram("Resources/Shaders/Basic.ver", "Resources/Shaders/Basic.frag");
	program1 = ShaderLoader::CreateProgram("Resources/Shaders/Basic.ver", "Resources/Shaders/Colour.frag");

	texture = TextureLoader::CreateTexture("Resources/Textures/Rayman.jpg");
	texture1 = TextureLoader::CreateTexture("Resources/Textures/AwesomeFace.png");

	camera.orthoInti(Utils::SCR_WIDTH, Utils::SCR_HEIGHT, 0.1f, 100.0f);

	MMenu1 = new MMenu;
	HMenu1 = new HMenu;
	EMenu1 = new EMenu;

	level1.LoadFromCSV("Resources/Levels/SpearGameLevel1.csv", &camera, program);

	player.initalise(GameInput, &camera, 100, 100, 0, 300, program, texture1, 0, texture);
	//player2.initalise(GameInput, &camera, 100, 100, 0, 0, program, texture, 1, texture1);
}

void CGameManager::update()
{
	
	bool up, down, confirm;

	up = GameInput->checkKeyDownFirst(KEY, GLFW_KEY_W);
	down = GameInput->checkKeyDown(KEY, GLFW_KEY_S);
	confirm = GameInput->checkKeyDown(KEY, GLFW_KEY_SPACE);

	if (confirm)
	{
		if (state = 0)
		{
			if (option = 0)
			{
				state = 1;
			}
			if (option = 1)
			{
				state = 2;
			}
			else
			{
				state = 0;
			}
		}
		if (state = 2)
		{
			state = 0;
		}
	}

	if (up)
	{
		option = option - 1;
	}

	if (down)
	{
		option = option + 1;
	}
		

	if (option > 2)
	{
		option = 0;
	}
	else if (option < 0)
	{
		option = 2;
	}
	
	deltaTime = std::chrono::high_resolution_clock::now() - previousTime;
	previousTime = std::chrono::high_resolution_clock::now();

	float DT = deltaTime.count() > 0.1f ? 0.1f : deltaTime.count();
	DT *= spdMultiplier;
	
	player.update(DT, level1.GetTiles());
	//player2.update(DT);
}

void CGameManager::render()
{
	if (state = 0)
	{
		MMenu1->RenderMM(option);
	}

	if (state = 1)
	{
		level1.Render();
		player.render();
		//player2.render();
	}

	if (state = 2)
	{
		HMenu1->RenderHM();
	}
}