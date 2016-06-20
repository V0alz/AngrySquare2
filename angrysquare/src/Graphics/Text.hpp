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
#pragma once

#include <map>
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

// PERSONAL NOTE: Move freetype stuff to deps folder.
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Transform.hpp"
#include "Shader.hpp"

struct Char
{
	GLuint m_texID;
	glm::ivec2 m_size;
	glm::vec2 m_offset;
	FT_Pos m_advance;
};

class Text
{
public:
	static bool Init( Shader& shader );
	static void Destroy();
	static void Render( const std::string& text, float x, float y, float scale );

private:
	static std::map<GLchar, Char> m_chars;
	static Transform m_transformation;
	static Shader* m_shader;
	static GLuint m_VAO;
	static GLuint m_VBO;
};
