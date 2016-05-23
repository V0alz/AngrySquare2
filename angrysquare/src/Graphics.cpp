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
#include "Graphics.hpp"
#include <iostream>

Graphics::Graphics()
{
	m_isReady = false;
}

Graphics::~Graphics()
{
}

bool Graphics::InitGL()
{
	if( m_isReady )
	{
		std::cout << "Graphics already initalzied!" << std::endl;
		return false;
	}

	WindowSettings* settings = new WindowSettings();
	if( Window::Create( settings ) == 0 )
	{
		glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
		glEnable( GL_DEPTH_TEST );

		m_isReady = true;
		delete settings;
		return true;
	}
	else
	{
		delete settings;
		return false;
	}
}

void Graphics::Destroy()
{
	Window::Destroy();
}
