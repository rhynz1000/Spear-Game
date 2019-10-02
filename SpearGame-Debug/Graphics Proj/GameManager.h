#pragma once

//local includes
#include "Input.h"
#include "Utils.h"
#include "Quad.h"
#include "Audio.h"
#include "TextLabel.h"
#include "Button.h"
#include "Player.h"
#include "CLevel.h"

enum GameState
{
	MainMenu,
	Game,
	HelpMenu,
	EndScreen,
};

class CGameManager
{
public:
	void initalise(CInput* input);
	void update();
	void render();
	void spdup() { spdMultiplier++; }
	void spddown() { spdMultiplier--; if (spdMultiplier < 0)spdMultiplier = 0; }
	//Loads a random level into the level object passed in
	void loadLevel(CLevel & level);
private:
	CInput* GameInput;
	CPlayer player, player2;
	CCamera camera;
	CLevel level1;

	CQuad MMenu1;
	CQuad HMenu1;
	CQuad EMenu1;
	CQuad Selector;

	float spdMultiplier = 1;
	int option;
	GameState state;

	std::chrono::duration<float> deltaTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> previousTime;
};