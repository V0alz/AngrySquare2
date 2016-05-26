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
#include "Mesh.hpp"
#include <iostream>

Mesh::Mesh()
{
	glGenVertexArrays( 1, &m_vao );
	glGenBuffers( 1, &m_vbo );
	glGenBuffers( 1, &m_ibo );
	m_size = 0;
}

Mesh::~Mesh()
{
	glDeleteBuffers( 1, &m_ibo );
	glDeleteBuffers( 1, &m_vbo );
	glDeleteVertexArrays( 1, &m_vbo );
}

void Mesh::Set( MeshData& data )
{
	m_size = data.Size();
	glBindVertexArray( m_vao );

	glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
	glBufferData( GL_ARRAY_BUFFER, data.m_vertex.size() * sizeof( glm::vec2 ), &data.m_vertex[0], GL_STATIC_DRAW );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0 );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ibo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_size * sizeof( unsigned int ), &data.m_indices[0], GL_STATIC_DRAW );

	glBindVertexArray( 0 );
}

void Mesh::Draw()
{
	glBindVertexArray( m_vao );

	glDrawElements( GL_TRIANGLES, m_size, GL_UNSIGNED_INT, (void*)0 );
	
	glBindVertexArray( 0 );
}
