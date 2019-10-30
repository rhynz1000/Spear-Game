#pragma once

#define SPEAR_CATEGORY					0b10000000
#define PLAYER_CATEGORY					0b01000000
#define PLATFORM_CATEGORY				0b00100000

#include <Box2D/Box2D.h>

//dependency includes
#include <glew.h>
//#include <freeglut.h>
#include <SOIL.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

//libary includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>
#include <filesystem>

#include "ShaderLoader.h"
#include "Texture.h"
#include "Camera.h"

#include "glfw3.h"

//utilities for use throughout the program

//utilities for use throughout the program

namespace
{
	static const unsigned int SCR_WIDTH = 1920;
	static const unsigned int SCR_HEIGHT = 1080;
	static const unsigned int B2_WIDTH = 32;
	static const unsigned int B2_HEIGHT = 18;
	static const float PPM = SCR_WIDTH / 32.0f;
};