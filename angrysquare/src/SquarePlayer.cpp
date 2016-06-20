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
#include "SquarePlayer.hpp"
#include "System\Input.hpp"
#include "Graphics\Loader\BMP.hpp"
#include "System\Time.hpp"

SquarePlayer::SquarePlayer( const std::string& tex )
{
	m_sprite = new Sprite( glm::vec2( 0.5f, 0.5f ), BMP::Load( tex ) );
	m_transform.Position( glm::vec3( 0.0f, 0.0f, 0.0f ) );
}

SquarePlayer::~SquarePlayer()
{
}

void SquarePlayer::Update()
{
	double _delta = Time::GetDelta();
	glm::vec3 pos;
	pos = m_transform.Position();

	if( Input::Get( GLFW_KEY_W ) )
	{
		pos.y += static_cast<float>(0.4f * _delta);
	}
	if( Input::Get( GLFW_KEY_S ) )
	{
		pos.y -= static_cast<float>(0.4f * _delta);
	}

	if( Input::Get( GLFW_KEY_A ) )
	{
		pos.x -= static_cast<float>(0.4f * _delta);
	}
	if( Input::Get( GLFW_KEY_D ) )
	{
		pos.x += static_cast<float>(0.4f * _delta);
	}

	m_transform.Position( pos );
}
