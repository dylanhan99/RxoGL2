#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include "../Constants.h"

class Font
{
private:
	std::string m_FilePath;
	unsigned int m_FontSize;
	std::unordered_map<char, Character> m_Characters;

	void Setup()
	{
		FT_Library lib;
		if (FT_Init_FreeType(&lib))
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		FT_Face face;
		if (FT_New_Face(lib, m_FilePath.c_str(), 0, &face))
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		FT_Set_Pixel_Sizes(face, 0, m_FontSize); // pixel_height is basically font size. width is at 0 and will scale according to height
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

		for (unsigned char c = 0; c < 128; c++)
		{
			// load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// generate texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			// now store character for later use
			Character newChar = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			m_Characters.insert(std::pair<char, Character>(c, newChar));
		}
		FT_Done_Face(face);
		FT_Done_FreeType(lib);
	}
public:
	Font(){}
	Font(std::string path, unsigned int fontSize)
		: m_FilePath(path), m_FontSize(fontSize)
	{ Setup(); }

	inline const Character& GetChar(const char& c) const { return m_Characters.at(c); }
};