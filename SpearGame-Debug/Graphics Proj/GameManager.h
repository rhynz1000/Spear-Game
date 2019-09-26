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
#include "Menu.h"
#include "Help.h"

class CGameManager
{
public:
	void initalise(CInput* input);
	void update();
	void render();
	void spdup() { spdMultiplier++; }
	void spddown() { spdMultiplier--; if (spdMultiplier < 0)spdMultiplier = 0; }

private:
	CInput* GameInput;
	CPlayer player, player2;
	CCamera camera;
	CLevel level1;
	MMenu* MMenu1;
	HMenu* HMenu1;

	float spdMultiplier = 1;
	int option;

	std::chrono::duration<float> deltaTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> previousTime;
};