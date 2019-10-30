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

enum GameState
{
	MainMenu,
	Game,
	HelpMenu,
	EndScreen,
	Lobby,
};

struct StickyInfo {
	b2Body* spearBody;
	b2Body* targetBody;
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

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

private:
	CInput* GameInput;
	CPlayer player1, player2;
	CCamera camera;
	CLevel level1;

	CQuad MMenu1;
	CQuad HMenu1;
	CQuad EMenu1;
	CQuad LMenu1;
	CQuad Selector;
	CQuad P1Cont;
	CQuad P2Cont;

	CQuad ScoreBoard;
	CQuad P1HBack;
	CQuad P1HRed;
	CQuad P1HGreen;
	CQuad P2HBack;
	CQuad P2HRed;
	CQuad P2HGreen;

	float spdMultiplier = 1;

	int option;
	int P1Connected;
	int P2Connected;
	GameState state;
	bool axisLast = false;
	bool confirmLast = false;

	float P1CurHealth;
	float P1MovHealth;
	float P2CurHealth;
	float P2MovHealth;

	bool dev = false;
	bool endgame = false;

	std::chrono::duration<float> deltaTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> previousTime;

	TextLabel victory, p1Health, p2Health, p1Dash, p2Dash, score;

	float phyTimeStep;

	std::vector<StickyInfo> spearsStuck;

	b2World* world;
};