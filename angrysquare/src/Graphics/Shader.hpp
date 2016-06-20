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

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <unordered_map>
#include <glm\glm.hpp>

class Shader
{
public:
	Shader();
	~Shader();
	void Bind();
	virtual bool Create( const std::string& filename ); // TODO: rewrite me

	void AddUniform( const std::string& name );
	void SetUniform( const std::string& name, const glm::mat4 value );

protected:
	bool CheckError( GLuint shader, bool lnkchk = false );
	std::string LoadFromFile( std::string file );

private:
	GLuint m_program;
	std::unordered_map<std::string, unsigned int> m_uniforms;
};
