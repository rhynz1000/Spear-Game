#pragma once

#include "glm.hpp"
#include "Utils.h"

enum AXIS {
	X,
	Y,
	Z,
};

class CCamera
{
public:
	CCamera();//constuctor
	~CCamera();//deconstructor
	void orthoInti(float initWidth, float initHeight, float near, float far);//initalize orthographic camera
	void perspInti(float initWidth, float initHeight, float fov, float near, float far);//initalise a perspective camera
	glm::mat4 getCamMat();//calculate and return camera projection * view matrix
	glm::vec3 getCamPos() { return camPos; } //return camera position
	void moveCamera(AXIS axis, float amount, bool relative);//move the camera position
	void moveLook(AXIS axis, float amount, bool relative);//move the look direction

private:
	glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 2.0f);//camera position
	glm::vec3 camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);//camera look direction
	glm::vec3 camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);//camera up direction
	glm::mat4 proj, view;//matices for camera
};