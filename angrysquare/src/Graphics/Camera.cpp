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
#include "Camera.hpp"

glm::vec3 Camera::m_position = glm::vec3( 0.0f, 0.0f, 0.1f );
glm::mat4 Camera::m_projection;

void Camera::Init()
{
	m_projection = glm::ortho( -3.0f, 3.0f, -3.0f, 3.0f, 0.1f, 2.0f );
}

glm::mat4 Camera::GetProjection()
{
	return m_projection;
}

glm::mat4 Camera::GetView()
{
	return glm::lookAt( m_position, glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
}
