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
#include "Text.hpp"
#include "Camera.hpp"

Graphics::Graphics()
{
	m_isReady = false;
	for( int i = 0; i < 2; i++ )
	{
		m_shader[i] = nullptr;
	}
}

Graphics::~Graphics()
{
	for( int i = 0; i < 2; i++ )
	{
		if( m_shader[i] != nullptr )
		{
			delete m_shader[i];
			m_shader[i] = nullptr;
		}
	}
	Window::Destroy();
	Text::Destroy();
}

bool Graphics::InitGL( WindowSettings& settings )
{
	if( m_isReady )
	{
		std::cout << "Graphics already initalzied!" << std::endl;
		return false;
	}

	if( Window::Create( &settings ) == 0 )
	{
		glewExperimental = GL_TRUE;
		GLenum e = glewInit();
		if( e != GLEW_OK )
		{
			std::cout << glewGetErrorString( e ) << std::endl;
			return false;
		}
		if( !GLEW_VERSION_3_3 )
		{
			std::cout << "Failed to find requested version OpenGL version.\nErrors may occur..." << std::endl;
		}

		Window::ClearColor( glm::vec3( 0.0f, 0.05f, 0.05f ) );
		glEnable( GL_DEPTH_TEST );

		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		glEnable( GL_CULL_FACE ); // cull back faces of sprites.
		glCullFace( GL_BACK );
		glFrontFace( GL_CW );

		Camera::Init();

		m_shader[0] = new Shader();
		if( !m_shader[0]->Create( "shader" ) )
		{
			delete m_shader[0];
			return false;
		}
		m_shader[0]->AddUniform( "_model" );
		m_shader[0]->AddUniform( "_view" );
		m_shader[0]->AddUniform( "_projection" );

		m_shader[1] = new Shader();
		if( !m_shader[1]->Create( "text" ) )
		{
			delete m_shader[1];
			return false;
		}
		m_shader[1]->AddUniform( "_model" );
		m_shader[1]->AddUniform( "_view" );
		m_shader[1]->AddUniform( "_projection" );
		m_shader[1]->AddUniform( "_color" );

		Text::Init( *m_shader[1] );

		m_isReady = true;
		return true;
	}
	else
	{
		return false;
	}
}

void Graphics::Destroy()
{
	for( int i = 0; i < 2; i++ )
	{
		if( m_shader[i] != nullptr )
		{
			delete m_shader[i];
			m_shader[i] = nullptr;
		}
	}
	Window::Destroy();
	Text::Destroy();
}

void Graphics::RequestShader( const int i )
{
	m_shader[i]->Bind();
	m_shader[i]->SetUniform( "_projection", Camera::GetProjection() );
	m_shader[i]->SetUniform( "_view", Camera::GetView() );
}
