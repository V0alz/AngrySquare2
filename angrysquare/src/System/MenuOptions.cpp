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
#include "MenuOptions.hpp"
#include "MenuManager.hpp"
#include "../Graphics/Loader/GCF.hpp"

MenuOptions::MenuOptions()
{
	m_items.clear();
	m_items.emplace_back( new MenuItem( 0, "Resolution: ", -2.4f ) );
	m_items.emplace_back( new MenuItem( 1, "Fullscreen: ", -2.0f ) );
	m_items.emplace_back( new MenuItem( 2, "VSync", -1.6f ) );
	m_items.emplace_back( new MenuItem( 3, "FPS cap: ", -1.2f ) );
	m_items.emplace_back( new MenuItem( 4, "Back", -0.5f ) );

	m_listX = -2.85f;
	m_settings = new WindowSettings( GCF::Load() );
	m_requireRefresh = false;
	m_resolution = 0;
	m_fps = 0;
}

MenuOptions::~MenuOptions()
{
	std::cout << "Options settings deleted..." << std::endl;
	if( m_settings != nullptr )
	{
		delete m_settings;
		m_settings = nullptr;
	}
}

void MenuOptions::Responses()
{
	_options o;
	switch( m_cursor )
	{
	case 0:
	{
		m_resolution++;
		if( m_resolution >= 2 )
		{
			m_resolution = 0;
		}
		glm::ivec2 r = o.m_resolutions[m_resolution];
		m_settings->m_width = r.x;
		m_settings->m_height = r.y;
		m_requireRefresh = true;
		break;
	}
	case 1:
	{
		m_settings->m_fullscreen = !m_settings->m_fullscreen;
		m_requireRefresh = true;
		break;
	}
	case 2:
	{
		m_settings->m_vsync = !m_settings->m_vsync;
		Window::SetVSync( m_settings->m_vsync );
		break;
	}
	case 3:
	{
		m_fps++;
		if( m_fps >= 6 )
		{
			m_fps = 0;
		}
		int fr = o.m_frameRates[m_fps];
		m_settings->m_fps = fr;
		break;
	}
	case 4:
	{
		GCF::Save( *m_settings );
		MenuManager::RequestPage( MenuManager::Pages::PAGE_MAIN );
		break;
	}
	default:
		break;
	}
}

void MenuOptions::ExtraRender( Graphics& gfx )
{
	std::stringstream str;

	str << m_settings->m_width << " x " << m_settings->m_height;
	Text::Render( str.str(), -1.4f, 1.2f, 0.007f, glm::vec3( 0.0f, 0.3f, 0.7f ) );

	str.clear();
	str.str( "" );
	str << static_cast<bool>(m_settings->m_fullscreen);
	Text::Render( str.str(), -1.4f, 0.8f, 0.007f, glm::vec3( 0.0f, 0.3f, 0.7f ) );

	str.clear();
	str.str( "" );
	str << static_cast<bool>(m_settings->m_vsync);
	Text::Render( str.str(), -1.4f, 0.4f, 0.007f, glm::vec3( 0.0f, 0.3f, 0.7f ) );

	str.clear();
	str.str( "" );
	str << static_cast<int>(m_settings->m_fps);
	Text::Render( str.str(), -1.4f, 0.0f, 0.007f, glm::vec3( 0.0f, 0.3f, 0.7f ) );

	if( m_requireRefresh )
	{
		Text::Render( "The game window needs to be restarted", -2.80f, -1.1f, 0.0035f, glm::vec3( 0.3f, 0.6f, 0.0f ) );
		Text::Render( "for some changes to take effect!", -2.7f, -1.3f, 0.0035f, glm::vec3( 0.3f, 0.4f, 0.0f ) );
	}
}
