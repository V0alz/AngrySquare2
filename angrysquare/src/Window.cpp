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
	glfwMakeContextCurrent( m_window );
	
	if( !m_window )
	{
		std::cout << "Failed to create window" << std::endl;
		return 2;
	}

	return 0;
}

void Window::Destroy()
{
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
	return static_cast<int>(glfwWindowShouldClose( m_window ));
}
