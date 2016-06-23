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


#define _option_resolutions 2
#define _option_frameRates 6
struct _options
{
	const glm::ivec2 m_resolutions[_option_resolutions] =
	{
		glm::ivec2( 800, 600 ),
		glm::ivec2( 1440, 960 )
	};

	const int m_frameRates[_option_frameRates] =
	{
		20,
		30,
		45,
		55,
		60,
		120
	};
};

class MenuOptions : public Menu
{
public:
	MenuOptions();
	~MenuOptions();
	virtual void Responses() override;
	virtual void ExtraRender( Graphics& gfx ) override;

private:
	WindowSettings* m_settings;
	bool m_requireRefresh;
	int m_resolution;
	int m_fps;
};
