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
#include <Windows.h>
#include "Input.hpp"

bool Input::m_keys[300] = { false };

void Input::Init()
{
	for( int c = 0; c < 300; c++ )
	{
		m_keys[c] = false;
	}

	glfwSetKeyCallback( Window::GetWindow(), &cb_key );
}

bool Input::Get( int keycode )
{
	return m_keys[keycode];
}

void Input::Set( int keycode, int action )
{
	switch( action )
	{
	case GLFW_PRESS:
		m_keys[keycode] = true;
		break;
	case GLFW_RELEASE:
		m_keys[keycode] = false;
		break;
	case GLFW_KEY_UNKNOWN:
	default:
		break;
	}
}

void Input::cb_key( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	UNREFERENCED_PARAMETER( window );
	UNREFERENCED_PARAMETER( scancode );
	UNREFERENCED_PARAMETER( mods );
	Set( key, action );
}
