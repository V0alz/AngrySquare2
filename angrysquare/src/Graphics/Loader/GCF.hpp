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

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "../WindowsSettings.hpp"

// GCF(Game Config File) is used to store game settings.
// This isn't the best way to save data, fyi...
class GCF
{
public:
	static WindowSettings Load()
	{
		WindowSettings settings;
		bool ready = false;

		std::ifstream fs;
		while( !ready )
		{
			fs.open( "settings.gcf", std::ios::binary );
			if( !fs.is_open() )
			{
				std::cout << "Unable to open settings, making default file." << std::endl;
				GCF::SaveDefault();
			}
			else
			{
				ready = true;
			}
		}

		char input[4];
		fs.read( input, sizeof( input ) );
		if( input[0] != 0x41 ||
			input[1] != 0x53 )
		{
			std::cout << "Attempted to open a false GCF." << std::endl;
			return settings;
		}

		/*if( input[2] != 0x33 )
		{
			std::cout << "GCF version wrong, unable to load file." << std::endl;
			return settings;
		}*/

		fs.seekg( 0x05 );
		fs >> settings.m_width;
		fs.seekg( 0x0A );
		fs >> settings.m_height;
		fs.seekg( 0x0F );
		fs >> settings.m_fullscreen;
		fs.seekg( 0x11 );
		fs >> settings.m_vsync;
		fs.seekg( 0x13 );
		fs >> settings.m_fps;

		std::cout << "Loaded Game Config File: " << "settings.gcf" << std::endl;
		return settings;
	}

	static void Save( WindowSettings& settings )
	{
		std::ofstream fs;
		fs.open( "settings.gcf", std::ios::binary );

		std::stringstream ss;
		ss << 'A' << 'S' << '2' << '0' << static_cast<char>(0)
			<< std::setw( 4 ) << std::setfill( '0' ) << settings.m_width << static_cast<char>(0)
			<< std::setw( 4 ) << std::setfill( '0' ) << settings.m_height << static_cast<char>(0)
			<< settings.m_fullscreen << static_cast<char>(0)
			<< settings.m_vsync << static_cast<char>(0)
			<< settings.m_fps << static_cast<char>(0)
			<< static_cast<char>(0);

		fs << ss.str();
		fs.close();
	}

	static void SaveDefault()
	{
		std::ofstream fs;
		fs.open( "settings.gcf", std::ios::binary );
		WindowSettings settings;

		std::stringstream ss;
		ss  << 'A' << 'S' << '2' << '0' << static_cast<char>(0)
			<< std::setw( 4 ) << std::setfill( '0' ) << settings.m_width << static_cast<char>(0)
			<< std::setw( 4 ) << std::setfill( '0' ) << settings.m_height << static_cast<char>(0)
			<< settings.m_fullscreen << static_cast<char>(0)
			<< settings.m_vsync << static_cast<char>(0)
			<< settings.m_fps << static_cast<char>(0)
			<< static_cast<char>(0);

		fs << ss.str();
		fs.close();
	}
};
