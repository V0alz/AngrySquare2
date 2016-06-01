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
#include "Sprite.hpp"
#include "MeshData.hpp"

Sprite::Sprite()
{
	m_mesh = nullptr;
}

Sprite::Sprite( glm::vec2 dimensions, GLuint tex )
{
	m_mesh = nullptr;
	m_mesh = new Mesh();
	Set( dimensions, tex );
}

Sprite::~Sprite()
{
	if( m_mesh != nullptr )
	{
		delete m_mesh;
		m_mesh = nullptr;
	}
	glDeleteTextures( 1, &m_texture );
}

void Sprite::Set( glm::vec2 dimensions, GLuint tex )
{
	MeshData data;
	float _x = dimensions.x / 2;
	float _y = dimensions.y / 2;

	data.Set( glm::vec2( -_x, +_y ), glm::vec2( 0.0f, 1.0f ) );
	data.Set( glm::vec2( +_x, +_y ), glm::vec2( 1.0f, 1.0f ) );
	data.Set( glm::vec2( +_x, -_y ), glm::vec2( 1.0f, 0.0f ) );
	data.Set( glm::vec2( -_x, -_y ), glm::vec2( 0.0f, 0.0f ) );
	data.AddFace( glm::ivec3( 0, 1, 2 ) );
	data.AddFace( glm::ivec3( 2, 3, 0 ) );

	m_mesh->Set( data );
	m_texture = tex;
}

void Sprite::Draw()
{
	glBindTexture( GL_TEXTURE_2D, m_texture );
	m_mesh->Draw();
}
