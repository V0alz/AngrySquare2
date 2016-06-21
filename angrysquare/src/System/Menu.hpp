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

#include <string>
#include <vector>
#include "../Graphics/Text.hpp"
#include "../Graphics/Graphics.hpp"

struct MenuItem
{
	unsigned int m_id;
	std::string m_title;
	float m_yOffset;

	MenuItem( const unsigned int id, const char* title, float offset )
	{
		m_id = id;
		m_title = title;
		m_yOffset = offset;
	}

	void Draw( int curid )
	{
		glm::vec3 color = glm::vec3( 1.0f, 1.0f, 1.0f );
		if( m_id == curid )
		{
			color = glm::vec3( 0.9f, 0.1f, 0.1f );
		}
		Text::Render( m_title, 1.95f, -1.2f - m_yOffset, 0.007f, color );
	}
};

class Menu
{
public:
	Menu();
	~Menu();
	void Update();
	void Render( Graphics& gfx );

private:
	std::vector<MenuItem*> m_items;
	unsigned int m_cursor;
};
