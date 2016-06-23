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
#include "MenuManager.hpp"
#include "Time.hpp"

MenuManager::Pages MenuManager::m_active = Pages::PAGE_MAIN;
Menu* MenuManager::m_mainMenu = nullptr;
Menu* MenuManager::m_child = nullptr;

void MenuManager::Init()
{
	m_active = Pages::PAGE_MAIN;
	m_mainMenu = new Menu();
	m_child = nullptr;
}

void MenuManager::Destroy()
{
	if( m_child != nullptr )
	{
		delete m_child;
		m_child = nullptr;
	}
	if( m_mainMenu != nullptr )
	{
		delete m_mainMenu;
		m_mainMenu = nullptr;
	}
}

void MenuManager::Update()
{
	static Timer last;
	switch( m_active )
	{
	case Pages::PAGE_MAIN:
	{
		if( m_child != nullptr )
		{
			delete m_child;
			m_child = nullptr;
		}
		m_mainMenu->Update();
		break;
	}
	case Pages::PAGE_OPTIONS:
	{
		if( m_child == nullptr )
		{
			m_child = new MenuOptions();
		}
		m_child->Update();
		break;
	}
	default:
		break;
	}
}

void MenuManager::Render( Graphics& gfx )
{
	switch( m_active )
	{
	case Pages::PAGE_MAIN:
	{
		if( m_child != nullptr )
		{
			delete m_child;
			m_child = nullptr;
		}
		m_mainMenu->Render( gfx );
		break;
	}
	case Pages::PAGE_OPTIONS:
	{
		if( m_child != nullptr )
		{
			m_child->Render( gfx );
		}
		break;
	}
	default:
		break;
	}
}

void MenuManager::RequestPage( Pages page )
{
	m_active = page;
}
