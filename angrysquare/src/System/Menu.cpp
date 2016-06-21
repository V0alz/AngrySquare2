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
#include "Menu.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include "../Graphics/Window.hpp"
#include "SysState.hpp"

Menu::Menu()
{
	m_items.clear();
	m_items.emplace_back( new MenuItem( 0, "Play", 0.0f ) );
	m_items.emplace_back( new MenuItem( 1, "Options", 0.5f ) );
	m_items.emplace_back( new MenuItem( 2, "Exit", 1.25f ) );

	m_cursor = 0;
}

Menu::~Menu()
{
	for( unsigned int i = 0; i < m_items.size(); i++ )
	{
		delete m_items.at( i );
	}
	m_items.clear();
}

void Menu::Update()
{
	static Timer last;
	Timer keyDelay = Time::GetTime();
	if( (keyDelay - last) >= 0.25f )
	{
		if( Input::Get( GLFW_KEY_W ) && (m_cursor > 0) )
		{
			m_cursor--;
			last = Time::GetTime();
		}

		if( Input::Get( GLFW_KEY_S ) && (m_cursor < m_items.size()-1) )
		{
			m_cursor++;
			last = Time::GetTime();
		}
	}

	if( Input::Get( GLFW_KEY_ENTER ) || 
		Input::Get( GLFW_KEY_SPACE ) )
	{
		switch( m_cursor )
		{
		case 0:
			SysState::Set( SysState::States::STATE_LOAD );
			break;
		case 1:
			break;
		case 2:
			SysState::Set( SysState::States::STATE_CLEANUP );
			break;
		default:
			break;
		}
	}
}

void Menu::Render( Graphics& gfx )
{
	Window::ClearColor( glm::vec3( 0.0f, 0.0f, 0.0f ) );
	Window::Clear();
	Window::ClearColor( glm::vec3( 0.0f, 0.0f, 0.3f ) );

	gfx.RequestShader( 1 );
	Text::Render( "Angry  Square  2", -2.8f, 1.85f, 0.015f, glm::vec3( 1.0f, 0.0f, 0.0f ) );

	for( unsigned int i = 0; i < m_items.size(); i++ ) 
	{
		m_items.at( i )->Draw( m_cursor );
	}

	if( m_cursor == 2 )
	{
		Text::Render( ":(", -2.0f, -1.0f, 0.015f, glm::vec3( 0.0f, 0.0f, 1.0f ) );
	}

	Text::Render( "Angry Square 2 - Copyright(C) Dennis Walsh.", -2.97f, -2.97f, 0.003f );
}
