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

#include "BaseObject.hpp"
#include "..\Graphics\Shader.hpp"

class AppleObject : public BaseObject
{
public:
	AppleObject( Sprite* sprite )
	{
		//BaseObject( sprite );
		m_sprite = sprite;
	}

	~AppleObject()
	{
	}

	virtual void Update()
	{
		glm::vec3 pos;
		pos = m_transformation.Position();

		m_bounds.Set( glm::vec2( pos.x - (0.25f / 2), pos.y - (0.25f / 2) ), glm::vec2( pos.x + (0.25f / 2), pos.y + (0.25f / 2) ) );
	}

	virtual void Draw( Shader& shader )
	{
		shader.SetUniform( "_model", m_transformation.GetModelMatrix() );
		m_sprite->Draw();
	}

private:

};
