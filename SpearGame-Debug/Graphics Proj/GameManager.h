#pragma once

//local includes
#include "Input.h"
#include "Utils.h"
#include "Quad.h"
#include "Audio.h"
#include "TextLabel.h"
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
	void devModeSwitch() { dev = !dev; }

private:
	CInput* GameInput;
	CPlayer player1, player2;
	CCamera camera;
	CLevel level1;

	CQuad MMenu1;
	CQuad HMenu1;
	CQuad EMenu1;
	CQuad Selector;

	float spdMultiplier = 1;

	int option;
	GameState state;
	bool axisLast = false;
	bool confirmLast = false;

	bool dev = false;
	bool endgame = false;

	std::chrono::duration<float> deltaTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> previousTime;

	TextLabel victory, p1Health, p2Health, p1Dash, p2Dash;
};