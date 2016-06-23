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
#include "Window.hpp"
#include "WindowsSettings.hpp"
#include <iostream>

GLFWwindow* Window::m_window = nullptr;

int Window::Create( WindowSettings* settings )
{
	if( glfwInit() == GL_FALSE )
	{
		std::cerr << "GLFW3 failed to initalize..." << std::endl;
		return 1;
	}

	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

	glfwWindowHint( GLFW_SAMPLES, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	if( settings->m_fullscreen )
	{
		//m_window = glfwCreateWindow( settings->m_width, settings->m_height, "Angry Square 2", glfwGetPrimaryMonitor(), NULL );
		return 3;
	}
	else
	{
		m_window = glfwCreateWindow( settings->m_width, settings->m_height, "Angry Square 2", NULL, NULL );
	}
	
	if( !m_window )
	{
		std::cout << "Failed to create window" << std::endl;
		return 2;
	}
	glfwMakeContextCurrent( m_window );

	glfwSwapInterval( static_cast<int>(settings->m_vsync) );

	return 0;
}

void Window::Destroy()
{
	glfwDestroyWindow( m_window );
	glfwTerminate();
}

void Window::Clear()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Window::SwapBuffers()
{
	glfwSwapBuffers( m_window );
}

bool Window::ShouldExit()
{
	// fix this funcing error
	if( !glfwWindowShouldClose( m_window ) )
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Window::SetVSync( int val )
{
	glfwSwapInterval( val );
}

void Window::ClearColor( glm::vec3 color )
{
	glClearColor( color.x, color.y, color.z, 1.0f );
}

GLFWwindow* Window::GetWindow()
{
	return m_window;
}
