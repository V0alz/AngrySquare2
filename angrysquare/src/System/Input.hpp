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

#include <GLFW\glfw3.h>
#include "../Graphics/Window.hpp"

#define NUM_OF_KEYS 434

class Input
{
public:
	static void Init();
	static bool Get( int keycode );
	inline static void Set( int keycode, int action );

private:
	static void cb_key( GLFWwindow* window, int key, int scancode, int action, int mods );

private:
	static bool m_keys[NUM_OF_KEYS];
};
