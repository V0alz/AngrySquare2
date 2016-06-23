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
#include "SquareEnemy.hpp"
#include "..\System\Input.hpp"
#include "..\Graphics\Loader\BMP.hpp"
#include "..\System\Time.hpp"

SquareEnemy::SquareEnemy( const std::string& tex )
{
	m_sprite = new Sprite( glm::vec2( 0.5f, 0.5f ), BMP::Load( tex ) );
	m_transform.Position( glm::vec3( 0.0f, 3.0f, 0.0f ) );
}

SquareEnemy::~SquareEnemy()
{
}

void SquareEnemy::Update()
{
	double _delta = Time::GetDelta();
	glm::vec3 pos;
	pos = m_transform.Position();

	glm::vec2 difference = glm::vec2( m_targetPos.x - pos.x, m_targetPos.y - pos.y );
	float distance = sqrt( (difference.x * difference.x) + (difference.y * difference.y) );
	glm::vec2 normal = glm::vec2( difference.x / distance, difference.y / distance );
	
	pos.x += normal.x * 0.5f * static_cast<float>(_delta);
	pos.y += normal.y * 0.5f * static_cast<float>(_delta);

	if( pos.x - 0.25f < -3.0f )
	{
		pos.x = -3.0f + 0.25f;
	}
	if( pos.y - 0.25f < -3.0f )
	{
		pos.y = -3.0f + 0.25f;
	}

	if( pos.x + 0.25f > 3.0f )
	{
		pos.x = 3.0f - 0.25f;
	}
	if( pos.y + 0.25f > 3.0f )
	{
		pos.y = 3.0f - 0.25f;
	}

	m_bounds.Set( glm::vec2( pos.x - (0.5f / 2), pos.y - (0.5f / 2) ), glm::vec2( pos.x + (0.5f / 2), pos.y + (0.5f / 2) ) );

	m_transform.Position( pos );
}
