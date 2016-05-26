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
#include "Shader.hpp"
#include <iostream>
#include <fstream>

Shader::Shader()
{
	m_program = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteProgram( m_program );
}

void Shader::Bind()
{
	glUseProgram( m_program );
}

// TODO: rewrite me
bool Shader::Create()
{
	GLuint vertex;
	vertex = glCreateShader( GL_VERTEX_SHADER );
	std::string src = LoadFromFile( "./res/shader/shader.v.glsl" );
	const char* v = src.c_str();
	glShaderSource( vertex, 1, &v, NULL );
	glCompileShader( vertex );
	if( CheckError( vertex ) )
	{
		return false;
	}

	GLuint fragment;
	fragment = glCreateShader( GL_FRAGMENT_SHADER );
	src = LoadFromFile( "./res/shader/shader.f.glsl" );
	const char* f = src.c_str();
	glShaderSource( fragment, 1, &f, NULL );
	glCompileShader( fragment );
	if( CheckError( fragment ) )
	{
		return false;
	}

	glAttachShader( m_program, vertex );
	glAttachShader( m_program, fragment );
	glLinkProgram( m_program );

	glDeleteShader( vertex );
	glDeleteShader( fragment );
	return true;
}

bool Shader::CheckError( GLuint shader, bool lnkchk )
{
	switch( lnkchk )
	{
	case false:
		{
			GLint success;
			glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
			if( !success )
			{
				GLchar infoLog[512];
				glGetShaderInfoLog( shader, 512, NULL, infoLog );
				std::cout << infoLog << std::endl;
				return true;
			}

			return false;
		}
	case true:
		{
			GLint success;
			glGetProgramiv( shader, GL_LINK_STATUS, &success );
			if( !success )
			{
				GLchar infoLog[512];
				glGetProgramInfoLog( shader, 512, NULL, infoLog );
				std::cout << infoLog << std::endl;
				return true;
			}

			return false;
		}
	}

	// never reach
	return false;
}

std::string Shader::LoadFromFile( std::string file )
{
	std::string ret = "";
	std::ifstream shader( file, std::ios::in );
	if( shader.is_open() )
	{
		std::string line;
		while( getline( shader, line ) )
		{
			line.append( "\n" );
			ret.append( line );
		}
		shader.close();
	}
	else
	{
		std::cout << "Shader reading failed" << std::endl;
		return ret;
	}

	return ret;
}
