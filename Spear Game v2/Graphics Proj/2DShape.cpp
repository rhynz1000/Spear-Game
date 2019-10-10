#include "2DShape.h"

C2DShape::C2DShape(){}

C2DShape::~C2DShape(){ body = 0; }

void C2DShape::Initalise(CCamera * newCamera, float sizeH, float sizeW, float initalX, float initalY, GLuint prog, GLuint tex, GLfloat* vertices, GLuint* indices, int verticeSize, int indicesSize)
{
	//set all perimiters for initalisation
	this->setProgram(prog);
	this->setTexture(tex);
	this->setCamera(newCamera);
	this->setIndiceCount(indicesSize / sizeof(GLuint));


	this->scale(X, sizeW);
	this->scale(Y, sizeH);
	this->translate(X, initalX, false);
	this->translate(Y, initalY, false);


	//create ebo, vbo and vao
	GLuint EBO, VBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticeSize, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		5 * sizeof(GLfloat),
		(GLvoid*)0
	);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		5 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat))
	);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void C2DShape::rotate(AXIS axis, float angle, bool relative)
{
	switch (axis)//change the rotation matrix for model matrix
	{
	case X:
		iAngle.x = (relative) ? iAngle.x + angle : angle;
		if (iAngle.x < 0) { iAngle.x += 360.0f; }
		rotationMatrixX = glm::rotate(glm::mat4(), glm::radians(iAngle.x), glm::vec3(1.0f, 0.0f, 0.0f));
		break;
	case Y:
		iAngle.y = (relative) ? iAngle.y + angle : angle;
		if (iAngle.y < 0) { iAngle.y += 360.0f; }
		rotationMatrixY = glm::rotate(glm::mat4(), glm::radians(iAngle.y), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case Z:
		iAngle.z = (relative) ? iAngle.z + angle : angle;
		if (iAngle.z < 0) { iAngle.z += 360.0f; }
		rotationMatrixZ = glm::rotate(glm::mat4(), glm::radians(iAngle.z), glm::vec3(0.0f, 0.0f, 1.0f));
		break;
	default:
		break;
	}
}

void C2DShape::translate(AXIS axis, float amount, bool relative)
{
	switch (axis)//change the translation matrix for model matrix
	{
	case X:
		objPosition.x = (relative) ? objPosition.x + amount : amount;
		break;
	case Y:
		objPosition.y = (relative) ? objPosition.y + amount : amount;
		break;
	default:
		break;
	}

	translationMatrix = glm::translate(glm::mat4(), objPosition);
}

void C2DShape::scale(AXIS axis, float amount)
{
	switch (axis)//change the scale matrix for model matrix
	{
	case X:
		objScale.x = amount;
		break;
	case Y:
		objScale.y = amount;
		break;
	default:
		break;
	}
	scaleMatrix = glm::scale(glm::mat4(), objScale);
}

glm::mat4 C2DShape::getModel()
{
	return (translationMatrix * rotationMatrixX * rotationMatrixY * rotationMatrixZ * scaleMatrix);//calculates and returns model matrix
}

void C2DShape::render(glm::mat4 anchor)
{
	//renders the shape giving the shader anything it may need
	glUseProgram(program);

	glm::mat4 model = anchor * this->getModel();
	glm::mat4 MVP = camera->getCamMat() * model;

	GLuint UniformLoc = glGetUniformLocation(program, "MVP");
	glUniformMatrix4fv(UniformLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	UniformLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(UniformLoc, 1, GL_FALSE, glm::value_ptr(model));

	UniformLoc = glGetUniformLocation(program, "colour");
	glUniform4fv(UniformLoc, 1, glm::value_ptr(objColour));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, IndiceCount, GL_UNSIGNED_INT, 0);
}

//update the sprite with the body pos and rotation
void C2DShape::update()
{
	if (body != 0)
	{
		b2Vec2 pos = body->GetPosition();
		float angle = body->GetAngle();

		this->translate(X, pos.x, false);
		this->translate(Y, pos.y, false);

		this->rotate(Z, glm::degrees(angle), false);
	}
}

//bool C2DShape::collision(C2DShape * other)
//{
//	glm::vec2 pos = getPos();
//	glm::vec2 scale = getScale();
//
//	glm::vec2 posOther = other->getPos();
//	glm::vec2 scaleOther = other->getScale();
//
//	if ((pos.x + (scale.x *0.5)/*right*/ > posOther.x - (scaleOther.x *0.5)/*left*/ && pos.x - (scale.x *0.5)/*left*/ < posOther.x + (scaleOther.x *0.5)/*right*/) &&
//		(pos.y + (scale.y *0.5)/*top*/ > posOther.y - (scaleOther.y *0.5)/*bottom*/ && pos.y - (scale.y *0.5)/*bottom*/ < posOther.y + (scaleOther.y *0.5)/*top*/))
//	{
//		return true;
//	}
//
//	return false;
//}
//
//bool C2DShape::collision(std::vector<C2DShape*> other)
//{
//	glm::vec2 pos = getPos();
//	glm::vec2 scale = getScale();
//
//	glm::vec2 posOther;
//	glm::vec2 scaleOther;
//	
//	for (auto it = other.begin(); it != other.end(); it++)
//	{
//		posOther = (*it)->getPos();
//		scaleOther = (*it)->getScale();
//		if ((pos.x + (scale.x *0.5)/*right*/ > posOther.x - (scaleOther.x *0.5)/*left*/ && pos.x - (scale.x *0.5)/*left*/ < posOther.x + (scaleOther.x *0.5)/*right*/) &&
//			(pos.y + (scale.y *0.5)/*top*/ > posOther.y - (scaleOther.y *0.5)/*bottom*/ && pos.y - (scale.y *0.5)/*bottom*/ < posOther.y + (scaleOther.y *0.5)/*top*/))
//		{
//			return true;
//		}
//	}
//
//	return false;
//}

void C2DShape::sleepSwitch()
{
	body->SetAwake(!body->IsAwake());
}
