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
	m_shader = nullptr;
}

Graphics::~Graphics()
{
	if( m_shader != nullptr )
	{
		delete m_shader;
		m_shader = nullptr;
	}
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
		glewExperimental = GL_TRUE;
		GLenum e = glewInit();
		if( e != GLEW_OK )
		{
			std::cout << glewGetErrorString( e ) << std::endl;
			delete settings;
			return false;
		}
		if( !GLEW_VERSION_3_3 )
		{
			std::cout << "Failed to find requested version OpenGL version.\nErrors may occur..." << std::endl;
		}
		glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
		glEnable( GL_DEPTH_TEST );
		glEnable( GL_CULL_FACE ); // cull back faces of sprites.
		glCullFace( GL_BACK );
		glFrontFace( GL_CW );
		glViewport( -1, 1, 1, -1 ); // keep the default viewport

		m_shader = new Shader();
		if( !m_shader->Create() )
		{
			delete settings;
			delete m_shader;
			return false;
		}

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
	if( m_shader != nullptr )
	{
		delete m_shader;
		m_shader = nullptr;
	}
	Window::Destroy();
}
