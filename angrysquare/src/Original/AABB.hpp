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

#include <glm\glm.hpp>

class AABB
{
public:
	AABB()
		:m_min(),
		m_max()
	{
	}

	~AABB()
	{
	}

	void Set( glm::vec2 min, glm::vec2 max )
	{
		m_min = min;
		m_max = max;
	}

	static bool Intersects( const AABB& A, const AABB& B )
	{
		if( A.m_min.x < B.m_max.x &&
			A.m_max.x > B.m_min.x &&
			A.m_min.y < B.m_max.y &&
			A.m_max.y > B.m_min.y )
		{
			return true;
		}
		else
		{
			return false;
		}

		return false;
	}
	

private:
	glm::vec2 m_min;
	glm::vec2 m_max;
};
