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
#include "Transform.hpp"

Transform::Transform()
{
	m_position = glm::vec3();
	m_rotation = glm::vec3();
}


Transform::Transform( glm::vec3 position, glm::vec3 rotation )
{
	m_position = position;
	m_rotation = rotation;
}

Transform::~Transform()
{

}

glm::mat4 Transform::GetModelMatrix()
{
	glm::mat4 _x, _y, _z;
	//_x = glm::rotate( m_rotation.x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
	//_y = glm::rotate( m_rotation.y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
	//_z = glm::rotate( m_rotation.z, glm::vec3( 0.0f, 0.0f, 1.0f ) );

	glm::mat4 t = glm::translate( glm::mat4( 1.0f ), m_position );
	glm::mat4 r = _x * _y * _z;
	return t;
}

glm::vec3& Transform::Position( void )
{
	return m_position;
}

void Transform::Position( const glm::vec3& pos )
{
	m_position = pos;
}

glm::vec3* Transform::Rotation()
{
	return &m_rotation;
}
