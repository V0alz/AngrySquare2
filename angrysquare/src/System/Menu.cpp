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
#include <Windows.h>
#include "Menu.hpp"
#include "MenuManager.hpp"
#include "Input.hpp"
#include "../Graphics/Window.hpp"
#include "SysState.hpp"

Timer Menu::m_keyLast = 0.0;

Menu::Menu()
{
	m_items.clear();
	m_items.emplace_back( new MenuItem( 0, "Play", 0.0f ) );
	m_items.emplace_back( new MenuItem( 1, "Original", 0.4f ) );
	m_items.emplace_back( new MenuItem( 2, "Options", 0.8f ) );
	m_items.emplace_back( new MenuItem( 3, "Exit", 1.5f ) );

	m_cursor = 0;
	m_listX = 1.82f;
	m_keyLast = Time::GetTime();
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
	Timer keyDelay = Time::GetTime();
	if( (keyDelay - m_keyLast) >= 0.15 )
	{
		if( Input::Get( GLFW_KEY_W ) && (m_cursor > 0) )
		{
			m_cursor--;
			m_keyLast = Time::GetTime();
		}

		if( Input::Get( GLFW_KEY_S ) && (m_cursor < m_items.size() - 1) )
		{
			m_cursor++;
			m_keyLast = Time::GetTime();
		}

		if( Input::Get( GLFW_KEY_ENTER ) ||
			Input::Get( GLFW_KEY_SPACE ) )
		{
			Responses();
			m_keyLast = Time::GetTime();
		}
	}

	if( Input::Get( GLFW_KEY_ESCAPE ) )
	{
		//SysState::Set( SysState::States::STATE_CLEANUP );
	}
}

void Menu::Responses()
{
	switch( m_cursor )
	{
	case 0:
		break;
	case 1:
		SysState::Set( SysState::States::STATE_LOAD_ORIGINAL );
		break;
	case 2:
		MenuManager::RequestPage( MenuManager::Pages::PAGE_OPTIONS );
		break;
	case 3:
		SysState::Set( SysState::States::STATE_CLEANUP );
		break;
	default:
		break;
	}
}

void Menu::Render( Graphics& gfx )
{
	Window::ClearColor( glm::vec3( 0.0f, 0.0f, 0.0f ) );
	Window::Clear();
	Window::ClearColor( glm::vec3( 0.0f, 0.05f, 0.05f ) );

	gfx.RequestShader( 1 );
	Text::Render( "Hungry  Square  2", -2.8f, 1.85f, 0.015f, glm::vec3( 1.0f, 0.0f, 0.0f ) );

	for( unsigned int i = 0; i < m_items.size(); i++ )
	{
		m_items.at( i )->Draw( m_cursor, m_listX );
	}

	ExtraRender( gfx );

	Text::Render( "Hungry Square 2 - Copyright(C) Dennis Walsh.", -2.97f, -2.97f, 0.0028f );
}

void Menu::ExtraRender( Graphics& gfx )
{
	UNREFERENCED_PARAMETER( gfx );
	if( m_cursor == 3 )
	{
		Text::Render( ":(", -2.0f, 1.0f, 0.015f, glm::vec3( 0.0f, 0.5f, 1.0f ) );
	}
}
