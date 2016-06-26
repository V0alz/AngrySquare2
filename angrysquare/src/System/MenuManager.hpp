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

#include "Menu.hpp"
#include "MenuOptions.hpp"

class MenuManager
{
public:
	enum Pages
	{
		PAGE_MAIN, // This is the menu root, has to be m_active init value.
		PAGE_OPTIONS
	};
public:
	static void Init();
	static void Destroy();
	static void Update();
	static void Render( Graphics& gfx );
	static void RequestPage( Pages page );

private:
	static Pages m_active;
	static Menu* m_mainMenu;
	static Menu* m_child;
};
