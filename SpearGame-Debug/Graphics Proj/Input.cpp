
#include "Input.h"

void CInput::keyboardDown(ORIGIN orig, int key)//changing states to down for keys on the keyboard
{
	switch (orig)
	{
	case KEY://statement for ascii keys
	{
		if (KeyState[key] == UP || KeyState[key] == UP_FIRST)
		{
			KeyState[key] = DOWN_FIRST;
		}
	}
		break;
	default:
		break;
	}
}

void CInput::keyboardUp(ORIGIN orig, int key)//changing states for up on the keyboard
{
	switch (orig)
	{
	case KEY://statement for ascii keys
	{
		if (KeyState[key] == DOWN || KeyState[key] == DOWN_FIRST)
		{
			KeyState[key] = UP_FIRST;
		}
	}
	break;
	default:
		break;
	}
}

void CInput::MouseMove(int x, int y)//mouse move for updating mouse x and y
{
	mousex = x;
	mousey = y;
}

void CInput::MouseClick(int button, int state)//mouse click states
{
	if (button >= 5)
		return;

	if ((MouseState[button] == DOWN || MouseState[button] == DOWN_FIRST) && (state == GLFW_PRESS))
	{
		MouseState[button] = UP_FIRST;
	}
	else if ((MouseState[button] == UP || MouseState[button] == UP_FIRST) && (state == GLFW_RELEASE))
	{
		MouseState[button] = DOWN_FIRST;
	}
}

void CInput::Update()// update for up and down fist implementation
{
	//iterates through all the arrays making any button with up or down first into corollating up or down
	for (int i = 0; i < 255; i++)
	{
		if (KeyState[i] == UP_FIRST)
		{
			KeyState[i] = UP;
		}
		else if (KeyState[i] == DOWN_FIRST)
		{
			KeyState[i] = DOWN;
		}
	}

	for (int i = 0; i < 21; i++)
	{
		if (spKeyState[i] == UP_FIRST)
		{
			spKeyState[i] = UP;
		}
		else if (spKeyState[i] == DOWN_FIRST)
		{
			spKeyState[i] = DOWN;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (MouseState[i] == UP_FIRST)
		{
			MouseState[i] = UP;
		}
		else if (MouseState[i] == DOWN_FIRST)
		{
			MouseState[i] = DOWN;
		}
	}
}

bool CInput::checkKeyDown(ORIGIN orig, int key)//check function for any down state
{
	switch (orig)
	{
	case KEY:
	{
		if (KeyState[key] == DOWN || KeyState[key] == DOWN_FIRST)
		{
			return true;
		}
	}
		break;
	case MOUSE:
	{
		if (MouseState[key] == DOWN || MouseState[key] == DOWN_FIRST)
		{
			return true;
		}
	}
		break;
	default:
		break;
	}
	return false;
}

bool CInput::checkKeyUp(ORIGIN orig, int key)//check function for any up states
{
	switch (orig)
	{
	case KEY:
	{
		if (KeyState[key] == UP || KeyState[key] == UP_FIRST)
		{
			return true;
		}
	}
	break;
	case MOUSE:
	{
		if (MouseState[key] == UP || MouseState[key] == UP_FIRST)
		{
			return true;
		}
	}
	break;
	default:
		break;
	}
	return false;
}


bool CInput::checkKeyDownFirst(ORIGIN orig, int key)//check function for down first state
{
	switch (orig)
	{
	case KEY:
	{
		if (KeyState[key] == DOWN_FIRST)
		{
			return true;
		}
	}
	break;
	case MOUSE:
	{
		if (MouseState[key] == DOWN_FIRST)
		{
			return true;
		}
	}
	break;
	default:
		break;
	}
	return false;
}

bool CInput::checkKeyUpFirst(ORIGIN orig, int key)//check function for up first state
{
	switch (orig)
	{
	case KEY:
	{
		if (KeyState[key] == UP_FIRST)
		{
			return true;
		}
	}
	break;
	case MOUSE:
	{
		if (MouseState[key] == UP_FIRST)
		{
			return true;
		}
	}
	break;
	default:
		break;
	}
	return false;
}

void CInput::getMousePos(int & X, int & Y)//returns the mouse position in the window
{
	X = mousex;
	Y = mousey;
}
glm::vec2 CInput::getMousePos()//returns the mouse position in the window
{
	return glm::vec2(mousex, mousey);
}
