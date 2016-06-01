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

#include <vector>
#pragma warning( disable : 4201 ) // this is to hide GLM warnings, easy temp fix tho.
#include <glm\glm.hpp>

struct MeshData
{ 
	std::vector<glm::vec2> m_vertex;
	std::vector<glm::vec2> m_uv;
	std::vector<unsigned int> m_indices;

	void Set( glm::vec2 vertex, glm::vec2 uv = glm::vec2() )
	{
		m_vertex.emplace_back( vertex );
		m_uv.emplace_back( uv );
	}

	void AddFace( glm::ivec3 face )
	{
		m_indices.emplace_back( face.x );
		m_indices.emplace_back( face.y );
		m_indices.emplace_back( face.z );
	}

	int Size()
	{
		return m_indices.size();
	}
};
