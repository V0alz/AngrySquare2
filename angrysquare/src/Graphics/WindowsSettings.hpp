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

struct WindowSettings
{
	int m_width;
	int m_height;
	bool m_fullscreen;
	bool m_vsync;
	char m_fps;

	WindowSettings()
	{
		m_width = 800;
		m_height = 600;
		m_fullscreen = false;
		m_vsync = false;
		m_fps = 30;
	}

	WindowSettings( WindowSettings& settings )
	{
		m_width = settings.m_width;
		m_height = settings.m_height;
		m_fullscreen = settings.m_fullscreen;
		m_vsync = settings.m_vsync;
		m_fps = settings.m_fps;
	}
};
