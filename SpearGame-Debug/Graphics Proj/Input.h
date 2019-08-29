#pragma once

#include "Utils.h"

//input origin based on key
enum ORIGIN
{
	KEY,
	SKEY,
	MOUSE,
};

class CInput
{
public:
	CInput() {};//constructor
	~CInput() {};//destructor
	void keyboardDown(ORIGIN orig, int key);//keyboard down for glut functions
	void keyboardUp(ORIGIN orig, int key);//keyboard up for glut functions
	void MouseMove(int x, int y);//mouse move location for glut functions
	void MouseClick(int button, int state);//mouse click for glut functions

	void Update();//update for first states

	bool checkKeyDown(ORIGIN orig, int key);//check down for all keys
	bool checkKeyUp(ORIGIN orig, int key);//check up for all keys
	bool checkKeyDownFirst(ORIGIN orig, int key);//check down first for all keys
	bool checkKeyUpFirst(ORIGIN orig, int key);//check up first for all keys
	void getMousePos(int &X, int &Y);//getting mouse position
	glm::vec2 getMousePos();
	bool isJoystickValid(int joystick) { return glfwJoystickIsGamepad(joystick); }
	GLFWgamepadstate getJoystickInput(int joystick);

private:
	//input states for keys
	enum InputState
	{
		UP,
		DOWN,
		UP_FIRST,
		DOWN_FIRST,
	};

	//array for keys
	InputState KeyState[348]{};
	InputState spKeyState[21]{};
	InputState MouseState[5]{};

	//mouse location;
	int mousex = 0, mousey = 0;
};