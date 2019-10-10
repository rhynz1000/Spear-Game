#include "TextLabel.h"

void TextLabel::init(std::string newText, std::string font, glm::vec2 pos, glm::vec3 colour, float scale)//creates a text object for the ui
{
	//set all needed variables
	text = newText;
	SetColour(colour);
	SetScale(scale);
	SetPosition(pos);

	//create the ui camera
	GLfloat halfWidth = (GLfloat)SCR_WIDTH*0.5;
	GLfloat halfHeight = (GLfloat)SCR_HEIGHT*0.5;
	proj = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight);
	//create the program for text rendering
	program = ShaderLoader::CreateProgram("Resources/Shaders/Text.ver", "Resources/Shaders/Text.frag");

	//load the font
	FT_Library ft;
	FT_Face face;

	if (FT_Init_FreeType(&ft) != 0)
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Libary" << std::endl;
		return;
	}

	if (FT_New_Face(ft, font.c_str(), 0, &face) != 0)
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte character = 0; character < 128; character++)
	{
		if (FT_Load_Char(face, character, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
			continue;
		}

		//generate the texture for the current letter
		GLuint texture = GenerateTexture(face);

		FontChar fontChar = { texture,
		glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
		glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
		(GLuint)face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, FontChar>(character, fontChar));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	//create a vbo and vao 
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6*4, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void TextLabel::Render()
{
	//render each letter positioning where they need to go
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(program);
	glUniform3f(glGetUniformLocation(program, "textColor"), colour.x, colour.y, colour.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_FALSE, glm::value_ptr(proj));
	glBindVertexArray(VAO);

	textWidth = 0;

	glm::vec2 textPos = position;
	for (std::string::const_iterator character = text.begin(); character != text.end(); character++)
	{
		FontChar fontChar = Characters[*character];
		GLfloat xpos = textPos.x + fontChar.Bearing.x *scale;
		GLfloat ypos = textPos.y - (fontChar.Size.y-fontChar.Bearing.y) *scale;
		GLfloat charWidth = fontChar.Size.x*scale;
		GLfloat charHeight = fontChar.Size.y*scale;

		textWidth += charWidth;

		GLfloat vertices[6][4] = {
			{ xpos, ypos + charHeight, 0.0, 0.0 }, { xpos, ypos, 0.0, 1.0 }, { xpos + charWidth, ypos, 1.0, 1.0 },
			{ xpos, ypos + charHeight, 0.0, 0.0 }, { xpos + charWidth, ypos, 1.0, 1.0 }, { xpos + charWidth, ypos + charHeight, 1.0, 0.0 },
		};

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fontChar.TextureID);
		glUniform1i(glGetUniformLocation(program, "tex"), 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		textPos.x += (fontChar.Advance >> 6)*scale;
	}
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//glDisable(GL_CULL_FACE);
	//glDisable(GL_BLEND);
}

GLuint TextLabel::GenerateTexture(FT_Face face)
{
	//generate the texture for a letter
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RED,
		face->glyph->bitmap.width,
		face->glyph->bitmap.rows,
		0,
		GL_RED, GL_UNSIGNED_BYTE,
		face->glyph->bitmap.buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;
}
