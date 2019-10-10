#pragma once

//local includes
#include <Box2D/Box2D.h>
#include "Input.h"
#include "Utils.h"
#include "Quad.h"
#include "Audio.h"
#include "TextLabel.h"
#include "Player.h"
#include "CLevel.h"
#include "Masks.h"

enum GameState
{
	MainMenu,
	Game,
	HelpMenu,
	EndScreen,
};

class CGameManager : b2ContactListener
{
public:
	CGameManager() {}
	~CGameManager() { delete world; }

	void initalise(CInput* input);
	void update();
	void render();
	void spdup() { spdMultiplier++; }
	void spddown() { spdMultiplier--; if (spdMultiplier < 0)spdMultiplier = 0; }
	//Loads a random level into the level object passed in
	void loadLevel(CLevel & level);
	void devModeSwitch() { dev = !dev; }

	//void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

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

	TextLabel victory, p1Health, p2Health, p1Dash, p2Dash, score;

	float phyTimeStep;

	b2World* world;
};