#include "gtc/matrix_transform.hpp"


#include "Camera.h"

CCamera::CCamera() {}

CCamera::~CCamera(){}

void CCamera::orthoInti(float scrWidth, float scrHeight, float n, float f)//initalise an ortographic camera
{
	float halfSCRWidth = scrWidth * 0.5f;
	float halfSCRHeight = scrHeight * 0.5f;
	proj = glm::ortho(-halfSCRWidth, halfSCRWidth, -halfSCRHeight, halfSCRHeight, n, f);
}

void CCamera::perspInti(float scrWidth, float scrHeight, float fov, float n, float f)//initalise a perspective camera
{
	proj = glm::perspective(fov, scrWidth/scrHeight, n, f);
}

glm::mat4 CCamera::getCamMat()//returns the projection * view matrix
{
	view = glm::lookAt(camPos, camPos + camLookDir, camUpDir);//calculates view matix
	return proj * view;
}

void CCamera::moveCamera(AXIS axis, float amount, bool relative)//move the camera
{
	//changes the camera position based on axis and if it is relative movement or not
	switch (axis)
	{
	case X:
		if (relative)
		{
			camPos += glm::cross(camLookDir, camUpDir) * amount;
		}
		else
		{
			camPos.x = amount;
		}
		break;
	case Y:
		if (relative)
		{
			camPos += camUpDir * amount;
		}
		else
		{
			camPos.y = amount;
		}
		break;
	case Z:
		if (relative)
		{
			camPos += glm::vec3(camLookDir.x, 0.0f, camLookDir.z) *amount;
		}
		else
		{
			camPos.z = amount;
		}
		break;
	default:
		break;
	}
	//view = glm::translate(view, objPosition);
}

void CCamera::moveLook(AXIS axis, float angle, bool relative)//rotates the cameras view through the look direction
{
	glm::mat4 rotation;

	switch (axis)
	{
	case X:
		if (relative)
		{
			rotation = glm::rotate(glm::mat4(), glm::radians(angle), glm::cross(camLookDir, camUpDir));
		}
		else
		{
			rotation = glm::rotate(glm::mat4(), glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		break;
	case Y:
		if (relative)
		{
			rotation = glm::rotate(glm::mat4(), glm::radians(angle), camUpDir);
		}
		else
		{
			rotation = glm::rotate(glm::mat4(), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		break;
	case Z:
		if (relative)
		{
			rotation = glm::rotate(glm::mat4(), glm::radians(angle), camLookDir);
		}
		else
		{
			rotation = glm::rotate(glm::mat4(), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		
		break;
	default:
		break;
	}
	camLookDir = glm::normalize(glm::vec3(rotation * glm::vec4(camLookDir, 1.0f)));
}
