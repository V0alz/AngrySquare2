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
