#pragma once
// Dependency Includes
#include <ft2build.h>
#include FT_FREETYPE_H

// Library Includes
#include <map>
#include <string>

// Local Includes
#include "Utils.h"

struct FontChar
{
	GLuint		TextureID;	// Texture ID 
	glm::ivec2	Size;		// Size of the glyph
	glm::ivec2  Bearing;	// Offset of the glyph (top left) from the baseline
	GLuint		Advance;	// How far to move for the next character
};

class TextLabel {
public:
	//textlabel constructor
	TextLabel() {};
	
	~TextLabel() {};//destructor

	void init(std::string newText,
		std::string font,
		glm::vec2 pos,
		glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f),
		float scale = 1.0f);

	void Render();//render function
	void SetText(std::string newText) { text = newText; };//sets text
	void SetColour(glm::vec3 newColour) { colour = newColour; };//sets colour
	void SetScale(GLfloat newScale) { scale = newScale; };//sets scale
	void SetPosition(glm::vec2 newPosition) { position = newPosition; };//sets position

	float getTextWidth() { return textWidth; }

private:
	GLuint GenerateTexture(FT_Face face);//texture generation

	//text properties
	std::string text;
	GLfloat scale;
	glm::vec3 colour;
	glm::vec2 position;

	float textWidth;
	
	//rendering variables
	GLuint VAO, VBO, program;
	glm::mat4 proj;

	//map of characters
	std::map<GLchar, FontChar> Characters;
};
