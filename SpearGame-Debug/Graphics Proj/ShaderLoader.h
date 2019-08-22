#pragma once

// Dependency Includes
#include <glew.h>
//#include <freeglut.h>
#include "Dependencies/GLFW/glfw3.h"

// Library Includes
#include <iostream>
#include <map>
#include<fstream>
#include<vector>

class ShaderLoader
{
	
public:
	ShaderLoader(void);
	~ShaderLoader(void);
	static GLuint CreateProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename);//creates a program from a vertex and fragment shader

private:
	static GLuint CreateShader(GLenum shaderType, const char* shaderName);//creates a shader
	static std::string ReadShaderFile(const char *filename);//reads the files
	static void PrintErrorDetails(bool isShader, GLuint id, const char* name);//printany errors
};
