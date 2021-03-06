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

#include <Windows.h>
#include "..\Graphics\Sprite.hpp"
#include "..\Graphics\Transform.hpp"
#include "AABB.hpp"

class BaseObject
{
public:
	BaseObject()
		:m_transformation( glm::vec3( 0.0f, 0.0f, 0.0f ) )
	{
		m_sprite = nullptr;
	}

	BaseObject( Sprite* sprite )
		:m_transformation( glm::vec3( 0.0f, 0.0f, 0.0f ) )
	{
		m_sprite = sprite;
	}

	virtual ~BaseObject()
	{
		if( m_sprite != nullptr )
		{
			delete m_sprite;
			m_sprite = nullptr;
		}
	}

	virtual void Update() {}
	virtual void Draw( Shader& shader ) { UNREFERENCED_PARAMETER( shader ); }
	virtual void Respawn() {}

	inline AABB& Bounds() { return m_bounds; };
	inline Transform& Transfromation() { return m_transformation; }

protected:
	Sprite* m_sprite;
	Transform m_transformation;
	AABB m_bounds;
};
