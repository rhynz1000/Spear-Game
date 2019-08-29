#pragma once
#include <glew.h>
//#include <freeglut.h>
#include <SOIL.h>
#include <vector>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Dependencies/GLFW/glfw3.h"

#include "Camera.h"
#include "Utils.h"


class C2DShape
{
public:
	C2DShape();//constructor
	~C2DShape();//destructor
	//initalises vao, vbo, ebo and any other variables for shape
	virtual void Initalise(CCamera* newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint tex, GLfloat* vertices, GLuint* indices, int verticeSize, int indicesSize);
	void setTexture(GLuint tex) { texture = tex; }//sets texture
	void setProgram(GLuint prog) { program = prog; }//sets program
	void setIndiceCount(GLuint count) { IndiceCount = count; }//sets indice count
	void setCamera(CCamera* newCamera) { camera = newCamera; }//sets camera pointer for shape
	void setColour(glm::vec4 color) { objColour = color; }//sets the colour
	void rotate(AXIS axis, float angle, bool relative);//sets rotation matrices
	void translate(AXIS axis, float amount, bool relative);//sets translation matrices
	void scale(AXIS axis, float amount);//sets scale matrices
	glm::mat4 getModel();//calculates model matrix and returns it
	glm::mat4 *getRefToModel() { return &model; }
	glm::vec2 getPos() { return glm::vec2(objPosition); }
	glm::vec2 getScale() { return glm::vec2(objScale); }
	glm::mat4 getRotationMat() { return rotationMatrixZ; }

	virtual void render(glm::mat4 anchor);//renders the shape

private:
	//transformation matrices
	glm::mat4 translationMatrix = glm::mat4();
	glm::mat4 rotationMatrixX = glm::mat4();
	glm::mat4 rotationMatrixY = glm::mat4();
	glm::mat4 rotationMatrixZ = glm::mat4();
	glm::mat4 scaleMatrix = glm::mat4();

	glm::mat4 model = glm::mat4();

	GLuint VAO;//vao for the shape

	//scale, angle and position for transformation matrices
	glm::vec3 objScale = glm::vec3(1.0f, 1.0f, 1.0f), iAngle = glm::vec3(0.0f, 0.0f, 0.0f), objPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec4 objColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	CCamera* camera;//camera object pointer

	GLuint texture;//texture
	GLuint program;//shape program
	GLuint IndiceCount;//number of indices
};