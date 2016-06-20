/*
*	Angry Square 2
*	Copyright(C) 2015-2016 Dennis Walsh
*
*	This program is free software : you can redistribute it and / or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
#include "Text.hpp"
#include <iostream>

std::map<GLchar, Char> Text::m_chars;
Transform Text::m_transformation;
Shader* Text::m_shader;
GLuint Text::m_VAO;
GLuint Text::m_VBO;

bool Text::Init( Shader& shader )
{
	m_shader = &shader;
	glGenVertexArrays( 1, &m_VAO );
	glGenBuffers( 1, &m_VBO );

	FT_Library m_freetype;
	FT_Face m_font;

	if( FT_Init_FreeType( &m_freetype ) )
	{
		std::cout << "Unable to initalize the freetype library!" << std::endl;
		return false;
	}

	if( FT_New_Face( m_freetype, "./res/font/AmaticSC-Regular.ttf", 0, &m_font ) )
	{
		std::cout << "Freetype could not open font!" << std::endl;
		return false;
	}

	glBindVertexArray( m_VAO );
	glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

	glBufferData( GL_ARRAY_BUFFER, sizeof( GLfloat ) * 6 * 4, NULL, GL_DYNAMIC_DRAW );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), 0 );

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray( 0 );

	FT_Set_Pixel_Sizes( m_font, 0, 64 );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	for( GLubyte c = 0; c < 128; c++ )
	{
		if( FT_Load_Char( m_font, c, FT_LOAD_RENDER ) )
		{
			std::cout << "FreeType fail to load Glyph" << std::endl;
			continue;
		}

		GLuint tex;
		glGenTextures( 1, &tex );
		glBindTexture( GL_TEXTURE_2D, tex );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RED, m_font->glyph->bitmap.width, m_font->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, m_font->glyph->bitmap.buffer );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		Char ch =
		{
			tex,
			glm::ivec2( m_font->glyph->bitmap.width, m_font->glyph->bitmap.rows ),
			glm::ivec2( m_font->glyph->bitmap_left, m_font->glyph->bitmap_top ),
			m_font->glyph->advance.x
		};
		m_chars.insert( std::pair<GLchar, Char>( c, ch ) );
	}

	glBindTexture( GL_TEXTURE_2D, 0 );

	FT_Done_Face( m_font );
	FT_Done_FreeType( m_freetype );

	return true;
}

void Text::Destroy()
{
	for( GLubyte c = 0; c < 128; c++ )
	{
		glDeleteTextures( 1, &m_chars.at( c ).m_texID );
	}

	glDeleteBuffers( 1, &m_VBO );
	glDeleteVertexArrays( 1, &m_VAO );
}

void Text::Render( const std::string& text, float x, float y, float scale )
{
	float place_x, place_y;
	place_x = place_y = 0.0f;

	glBindVertexArray( m_VAO );
	m_transformation.Position( glm::vec3( x, y, 0.0f ) );
	m_shader->SetUniform( "_model", m_transformation.GetModelMatrix() );

	std::string::const_iterator c;
	for( c = text.begin(); c != text.end(); c++ )
	{
		Char ch = m_chars[*c];

		float _x = place_x + ch.m_offset.x * scale;
		float _y = place_y - (ch.m_size.y - ch.m_offset.y) * scale;

		float w = ch.m_size.x * scale;
		float h = ch.m_size.y * scale;

		GLfloat vertices[6][4] = {
			{ _x,     _y + h,   0.0, 0.0 },
			{ _x,     _y,       0.0, 1.0 },
			{ _x + w, _y,       1.0, 1.0 },

			{ _x,     _y + h,   0.0, 0.0 },
			{ _x + w, _y,       1.0, 1.0 },
			{ _x + w, _y + h,   1.0, 0.0 }
		};

		glBindTexture( GL_TEXTURE_2D, ch.m_texID );

		glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
		glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( vertices ), vertices );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		glDrawArrays( GL_TRIANGLE_STRIP, 0, 6 );

		place_x += (ch.m_advance >> 6) * scale;
	}

	glBindVertexArray( 0 );
	glBindTexture( GL_TEXTURE_2D, 0 );
}
