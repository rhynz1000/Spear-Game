#include "GameManager.h"

GLuint program, program1;
CQuad testPlat, testPlay;

void CGameManager::initalise(CInput* input)
{
	camera.orthoInti(B2_WIDTH, B2_HEIGHT, 0.1f, 100.0f);

	b2Vec2 gravity(0.0f, -10.0f);

	world = new b2World(gravity);

	world->SetSubStepping(true);

	world->SetContactListener(this);

	state = MainMenu;
	option = 0;
	P1Connected = 0;
	P2Connected = 0;
	GameInput = input;
	program = ShaderLoader::CreateProgram("Resources/Shaders/Basic.ver", "Resources/Shaders/Basic.frag");
	program1 = ShaderLoader::CreateProgram("Resources/Shaders/Basic.ver", "Resources/Shaders/Colour.frag");

	MMenu1.Initalise(&camera, B2_HEIGHT, B2_WIDTH, 0, 0, program, TextureLoader::get("MainMenu"));

	HMenu1.Initalise(&camera, B2_HEIGHT, B2_WIDTH, 0, 0, program, TextureLoader::get("HelpMenu"));

	EMenu1.Initalise(&camera, B2_HEIGHT, B2_WIDTH, 0, 0, program, TextureLoader::get("EndMenu"));

	LMenu1.Initalise(&camera, B2_HEIGHT, B2_WIDTH, 0, 0, program, TextureLoader::get("LobbyMenu"));

	Selector.Initalise(&camera, 30/PPM, 50/PPM, -130/PPM, 0, program, TextureLoader::get("Selector"));

	P2Cont.Initalise(&camera, 300 / PPM, 500 / PPM, 400 / PPM, -20 / PPM, program, TextureLoader::get("Controller"));
	P1Cont.Initalise(&camera, 300 / PPM, 500 / PPM, -400 / PPM, -20 / PPM, program, TextureLoader::get("Controller"));

	player1.initalise(GameInput, &camera, 100/PPM, 50 / PPM, 0, 300 / PPM, program, TextureLoader::get("player1"), 0, TextureLoader::get("spear"), world);
	player1.setId(1);
	player2.initalise(GameInput, &camera, 100 / PPM, 50 / PPM, 0, 0, program, TextureLoader::get("player2"), 1, TextureLoader::get("spear"), world);
	player2.setId(2);

	victory.init("", "Resources/Fonts/arial.ttf", glm::vec2(), glm::vec3(), 1);
	p1Health.init("P1 Health: ", "Resources/Fonts/arial.ttf", glm::vec2((-(int)SCR_WIDTH / 2) + 10, (-(int)SCR_HEIGHT / 2) + 20), glm::vec3(1,1,1), 1);
	p2Health.init("P2 Health: ", "Resources/Fonts/arial.ttf", glm::vec2(((int)SCR_WIDTH / 2) - 350, (-(int)SCR_HEIGHT / 2) + 20), glm::vec3(1, 1, 1), 1);
	p1Dash.init("P1 Dash: ", "Resources/Fonts/arial.ttf", glm::vec2((-(int)SCR_WIDTH / 2) + 10, (-(int)SCR_HEIGHT / 2) + 60), glm::vec3(1, 1, 1), 1);
	p2Dash.init("P2 Dash: ", "Resources/Fonts/arial.ttf", glm::vec2(((int)SCR_WIDTH / 2) - 350, (-(int)SCR_HEIGHT / 2) + 60), glm::vec3(1, 1, 1), 1);
	score.init("0 : 0", "Resources/Fonts/arial.ttf", glm::vec2(-50, ((int)SCR_HEIGHT / 2) - 70), glm::vec3(1,1,1), 1);

	//testPlat.Initalise(&camera, 1, 6, 0, -3, program1, 0,world, b2_staticBody, PLATFORM_CATEGORY, PLAYER_CATEGORY);
	//testPlat.setColour(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	//testPlay.Initalise(&camera, 1, 1, 0, 0, program1, 0, world, b2_dynamicBody, PLAYER_CATEGORY, PLATFORM_CATEGORY);
	//testPlay.setColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
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
			CAudio::getInstance()->playSound("Select", 0.3f);
			switch (state)
			{
			case MainMenu:
			{
				if (option == 0)
				{
					//if ((GameInput->isJoystickValid(0)) || dev)
					//{
					//	loadLevel(level1);
					//	state = Game;
					//}
					//else
					//{
					//	std::cout << "No Controller Connected" << std::endl;
					//}

					state = Lobby;
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

			case HelpMenu:
			{
				state = MainMenu;
			}
			break;

			case EndScreen:
			{
				if (endgame)
				{
					player1.resetScore();
					player2.resetScore();
					score.SetText("0 : 0");
					state = MainMenu;
				}
				else
				{
					loadLevel(level1);
					state = Game;
				}
			}
			break;

			case Lobby:
			{
				if (P1Connected == 1 && P2Connected == 1)
				{
					loadLevel(level1);
					state = Game;
				}
				else
				{
					std::cout << "Not enough players." << std::endl;
				}
			}

			default:
				break;
			}


		}
		if (state == MainMenu)
		{
			if (up)
			{
				CAudio::getInstance()->playSound("MouseOver", 0.3f);
				option = option - 1;
			}
			else if (down)
			{
				CAudio::getInstance()->playSound("MouseOver", 0.3f);
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
				Selector.translate(Y, 80 / PPM, false);
			}
			break;
			case 1:
			{
				Selector.translate(Y, -140 / PPM, false);
			}
			break;
			case 2:
			{
				Selector.translate(Y, -360 / PPM, false);
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
			CAudio::getInstance()->playSound("Death", 0.3f);
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
				victory.SetPosition(glm::vec2(-160/PPM, 0));
				endgame = true;
				state = EndScreen;
			}
			else if (player2.getScore() >= 2)
			{
				victory.SetText("Player 2 wins");
				victory.SetPosition(glm::vec2(-160/PPM, 0));
				endgame = true;
				state = EndScreen;
			}
			else
			{
				score.SetText(std::to_string(player1.getScore()) + " : " + std::to_string(player2.getScore()));
				loadLevel(level1);
				//victory.SetPosition(glm::vec2(-50, 0));
			}
			player1.reset();
			player2.reset();
			//state = Game;
		}

		phyTimeStep += DT;

		//do physics calculations 60 times per second
		if (phyTimeStep >= 1 / 60)
		{
			player1.setGrounded(false);
			player2.setGrounded(false);
			world->Step(phyTimeStep, 10, 8);
			world->ClearForces();
			phyTimeStep = 0;

			if (spearStuck)
			{
				world->CreateJoint(&spearJoint);
				spearStuck = false;
			}

		}
		/*testPlay.update();*/
	}

	if (state == Lobby)
	{
		if ((GameInput->isJoystickValid(0)))
		{
			GLFWgamepadstate gpState = GameInput->getJoystickInput(0);
			if (gpState.buttons[GLFW_GAMEPAD_BUTTON_A])
			{
				P1Connected = 1;
			}
		}

		if ((GameInput->isJoystickValid(1)))
		{
			GLFWgamepadstate gp2State = GameInput->getJoystickInput(1);
			if (gp2State.buttons[GLFW_GAMEPAD_BUTTON_A])
			{
				P2Connected = 1;
			}
		}

	}

	if (!(GameInput->isJoystickValid(0)))
	{
		P1Connected = 0;
	}
	if (!(GameInput->isJoystickValid(1)))
	{
		P2Connected = 0;
	}

	CAudio::getInstance()->update();
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
		score.Render();
		/*testPlat.render(glm::mat4());
		testPlay.render(glm::mat4());*/
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
	case Lobby:
	{
		LMenu1.render(glm::mat4());
		if (P1Connected == 1)
		{
			P1Cont.render(glm::mat4());
		}
		if (P2Connected == 1)
		{
			P2Cont.render(glm::mat4());
		}
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
	level.LoadFromCSV(levelPaths[rand() % levelPaths.size()], &camera, program, world);
	levelPaths.clear();
}

void CGameManager::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{

	if ((int)contact->GetFixtureA()->GetBody()->GetUserData() == 1 && (int)contact->GetFixtureB()->GetBody()->GetUserData() == 3)
	{
		if (contact->GetFixtureA()->GetAABB(0).lowerBound.y + 2.0f * b2_linearSlop > contact->GetFixtureB()->GetAABB(0).upperBound.y)
		{
			player1.setGrounded(true);
		}
	}
	else if ((int)contact->GetFixtureA()->GetBody()->GetUserData() == 2 && (int)contact->GetFixtureB()->GetBody()->GetUserData() == 3)
	{
		if (contact->GetFixtureA()->GetAABB(0).lowerBound.y + 2.0f * b2_linearSlop> contact->GetFixtureB()->GetAABB(0).upperBound.y)
		{
			player2.setGrounded(true);
		}
	}
	else if ((int)contact->GetFixtureA()->GetBody()->GetUserData() == 3 && (int)contact->GetFixtureB()->GetBody()->GetUserData() == 4)
	{
		spearStuck = true;
		spearJoint.bodyA = contact->GetFixtureA()->GetBody();
		spearJoint.bodyB = contact->GetFixtureB()->GetBody();
		spearJoint.localAnchorA = contact->GetFixtureA()->GetBody()->GetLocalPoint(contact->GetFixtureB()->GetBody()->GetPosition());
		//spearJoint.localAnchorB;
	}
}
