#include "GameManager.h"

GLuint program, program1;

void CGameManager::initalise(CInput* input)
{
	state = MainMenu;
	option = 0;
	GameInput = input;
	program = ShaderLoader::CreateProgram("Resources/Shaders/Basic.ver", "Resources/Shaders/Basic.frag");
	program1 = ShaderLoader::CreateProgram("Resources/Shaders/Basic.ver", "Resources/Shaders/Colour.frag");

	camera.orthoInti(Utils::SCR_WIDTH, Utils::SCR_HEIGHT, 0.1f, 100.0f);

	MMenu1.Initalise(&camera, Utils::SCR_HEIGHT, Utils::SCR_WIDTH, 0, 0, program, TextureLoader::get("MainMenu"));

	HMenu1.Initalise(&camera, Utils::SCR_HEIGHT, Utils::SCR_WIDTH, 0, 0, program, TextureLoader::get("HelpMenu"));

	EMenu1.Initalise(&camera, Utils::SCR_HEIGHT, Utils::SCR_WIDTH, 0, 0, program, TextureLoader::get("EndMenu"));

	Selector.Initalise(&camera, 30, 50, -130, 0, program, TextureLoader::get("Selector"));

	player.initalise(GameInput, &camera, 100, 50, 0, 300, program, TextureLoader::get("player1"), 0, TextureLoader::get("spear"));
	player2.initalise(GameInput, &camera, 100, 50, 0, 0, program, TextureLoader::get("player2"), 1, TextureLoader::get("spear"));
}

void CGameManager::update()
{
	
	bool up, down, confirm;

	if (state != Game)
	{
		up = GameInput->checkKeyDownFirst(KEY, GLFW_KEY_UP);
		down = GameInput->checkKeyDownFirst(KEY, GLFW_KEY_DOWN);
		confirm = GameInput->checkKeyDownFirst(KEY, GLFW_KEY_ENTER);

		if (confirm)
		{
			CAudio::getInstance()->playSound("Select", 0.3);
			switch (state)
			{
			case 0:
			{
				if (option == 0)
				{
					loadLevel(level1);
					state = Game;
				}
				else if (option == 1)
				{
					state = HelpMenu;
				}
				else
				{
					exit(0);
				}
			}
			break;

			case 2:
			{
				state = MainMenu;
			}
			break;

			case 3:
			{
				state = MainMenu;
			}
			break;

			default:
				break;
			}


		}
		if (state == MainMenu)
		{
			if (up)
			{
				CAudio::getInstance()->playSound("MouseOver", 0.3);
				option = option - 1;
			}
			else if (down)
			{
				CAudio::getInstance()->playSound("MouseOver", 0.3);
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

			switch (option)
			{
			case 0:
			{
				Selector.translate(Y, 80, false);
			}
			break;
			case 1:
			{
				Selector.translate(Y, -140, false);
			}
			break;
			case 2:
			{
				Selector.translate(Y, -360, false);
			}
			break;
			default:
				break;
			}

		}
	}
	else
	{
		deltaTime = std::chrono::high_resolution_clock::now() - previousTime;
		previousTime = std::chrono::high_resolution_clock::now();

		float DT = deltaTime.count() > 0.1f ? 0.1f : deltaTime.count();
		DT *= spdMultiplier;

		player.update(DT, level1.GetTiles(), player2);
		player2.update(DT, level1.GetTiles(), player);

		if (player.getHealth() <= 0 || player2.getHealth() <= 0)
		{
			CAudio::getInstance()->playSound("Death", 0.3);
			state = EndScreen;
			player.reset();
			player2.reset();
		}
	}
}

void CGameManager::render()
{
	switch (state)
	{
	case MainMenu:
	{
		MMenu1.render(glm::mat4());
		Selector.render(glm::mat4());
	}
		break;
	case Game:
	{
		level1.Render();
		player.render();
		player2.render();
	}
		break;
	case HelpMenu:
	{
		HMenu1.render(glm::mat4());
	}
		break;
	case EndScreen:
	{
		EMenu1.render(glm::mat4());
	}
		break;
	default:
		break;
	}	
}

void CGameManager::loadLevel(CLevel & level)
{
	std::vector<std::string> levelPaths;
	for (std::experimental::filesystem::directory_entry entry : std::experimental::filesystem::directory_iterator("Resources/Levels")) {
		if (entry.path().extension() == ".csv") {
			levelPaths.push_back(entry.path().string());
		}
	}
	level.LoadFromCSV(levelPaths[rand() % levelPaths.size()], &camera, program);
	levelPaths.clear();
}
