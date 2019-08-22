#pragma once
//dependency includes
#include <glew.h>
//#include <freeglut.h>
#include <SOIL.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Dependencies/GLFW/glfw3.h"

//libary includes
#include <iostream>
#include <ctime>
#include <chrono>


#include "ShaderLoader.h"
#include "Texture.h"
#include "Camera.h"

//utilities for use throughout the program


class Utils
{
public:
	static const unsigned int SCR_WIDTH = 800;
	static const unsigned int SCR_HEIGHT = 600;
};