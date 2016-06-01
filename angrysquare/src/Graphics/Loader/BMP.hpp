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
#include <fstream>
#include <sstream>
#include <string>
#include <gl\glew.h>
#include <GLFW\glfw3.h>

struct bmp
{
	char header[54];
	unsigned int start;
	unsigned int width;
	unsigned int height;
	unsigned int size;
};

class BMP
{
public:
	static int Load( std::string file )
	{
		std::ifstream fs;
		fs.open( file, std::ios::binary );
		if( !fs.is_open() )
		{
			std::cout << "Unable to open " << file << std::endl;
			return 0;
		}

		bmp data;

		fs.read( data.header, sizeof( data.header ) );
		if( data.header[0] != 0x42 ||
			data.header[1] != 0x4d )
		{
			std::cout << "Not a valid BMP file!" << std::endl;
			return 0;
		}

		if( data.header[28] != 24 &&
			data.header[28] != 32 )
		{
			std::cout << "Attempted to load a non 24bit or 32bit image." << std::endl;
			return 0;
		}

		data.start = static_cast<int>(data.header[0x0A]);
		data.width = static_cast<int>(data.header[0x12]);
		data.height = static_cast<int>(data.header[0x16]);
		data.size = static_cast<int>(data.header[0x22]);

		if( data.size == 0 )
		{
			data.size = data.width * data.height * 3;
		}

		if( data.start == 0 )
		{
			data.start = 54;
		}

		unsigned char* image = new unsigned char[data.size];
		if( fs.is_open() )
		{
			fs.seekg( data.start, fs.beg );
			fs.read( (char*)image, data.size );
			fs.close();
		}

		GLuint texID;
		glGenTextures( 1, &texID );

		glBindTexture( GL_TEXTURE_2D, texID );

		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, data.width, data.height, 0, GL_BGR, GL_UNSIGNED_BYTE, image );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );

		glBindTexture( GL_TEXTURE_2D, 0 );

		delete[] image;

		std::cout << "Loaded " << file << std::endl;
		return texID;
	}
};
