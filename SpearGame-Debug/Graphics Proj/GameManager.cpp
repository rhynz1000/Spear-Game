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
	victory.init("", "Resources/Fonts/arial.ttf", glm::vec2(), glm::vec3(), 1);
	p1Health.init("P1 Health: ", "Resources/Fonts/arial.ttf", glm::vec2((-(int)Utils::SCR_WIDTH / 2) + 10, (-(int)Utils::SCR_HEIGHT / 2) + 20), glm::vec3(), 1);
	p2Health.init("P2 Health: ", "Resources/Fonts/arial.ttf", glm::vec2(((int)Utils::SCR_WIDTH / 2) - 350, (-(int)Utils::SCR_HEIGHT / 2) + 20), glm::vec3(), 1);
	p1Dash.init("P1 Dash: ", "Resources/Fonts/arial.ttf", glm::vec2((-(int)Utils::SCR_WIDTH / 2) + 10, (-(int)Utils::SCR_HEIGHT / 2) + 60), glm::vec3(), 1);
	p2Dash.init("P2 Dash: ", "Resources/Fonts/arial.ttf", glm::vec2(((int)Utils::SCR_WIDTH / 2) - 350, (-(int)Utils::SCR_HEIGHT / 2) + 60), glm::vec3(), 1);

}

void CGameManager::update()
{
	
	bool up, down, confirm;

	if (state != Game)
	{
		up = GameInput->checkKeyDownFirst(KEY, GLFW_KEY_UP);
		down = GameInput->checkKeyDownFirst(KEY, GLFW_KEY_DOWN);
		confirm = GameInput->checkKeyDownFirst(KEY, GLFW_KEY_ENTER);

		if (GameInput->isJoystickValid(0))
		{
			GLFWgamepadstate gpState = GameInput->getJoystickInput(0);
			up = gpState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] < -0.5 && !axisLast;
			down = gpState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] > 0.5 && !axisLast;

			axisLast = gpState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] < -0.5 || gpState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] > 0.5;

			confirm = gpState.buttons[GLFW_GAMEPAD_BUTTON_A] && !confirmLast;
			confirmLast = gpState.buttons[GLFW_GAMEPAD_BUTTON_A];
		}

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
				if (endgame)
				{
					player1.resetScore();
					player2.resetScore();
					state = MainMenu;
				}
				else
				{
					state = Game;
				}
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

		player1.update(DT, level1.GetTiles(), player2);
		player2.update(DT, level1.GetTiles(), player1);

		p1Health.SetText("P1 Health : " + std::to_string((int)player1.getHealth()));
		p2Health.SetText("P2 Health : " + std::to_string((int)player2.getHealth()));
		p1Dash.SetText("Dash : " + std::to_string(player1.isDashReady()));
		p2Dash.SetText("Dash : " + std::to_string(player2.isDashReady()));

		if (player1.getHealth() <= 0 || player2.getHealth() <= 0)
		{
			CAudio::getInstance()->playSound("Death", 0.3);
			if (player1.getHealth() <= 0)
			{
				player2.addPoint();
			}
			else
			{
				player1.addPoint();
			}

			if (player1.getScore() >= 2)
			{
				victory.SetText("Player 1 wins");
				victory.SetPosition(glm::vec2(-160, 0));
				endgame = true;
			}
			else if (player2.getScore() >= 2)
			{
				victory.SetText("Player 2 wins");
				victory.SetPosition(glm::vec2(-160, 0));
				endgame = true;
			}
			else
			{
				victory.SetText(std::to_string(player1.getScore()) + " : " + std::to_string(player2.getScore()));
				victory.SetPosition(glm::vec2(-50, 0));
			}
			state = EndScreen;
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
		player1.render();
		player2.render();
		p1Health.Render();
		p2Health.Render();
		p1Dash.Render();
		p2Dash.Render();
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
		victory.Render();
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
