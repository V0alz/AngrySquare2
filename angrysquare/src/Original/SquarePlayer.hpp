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

#include "Square.hpp"

class SquarePlayer : public Square
{
public:
	SquarePlayer( const std::string& tex = "./res/tex/player.bmp" );
	~SquarePlayer();
	virtual void Update() override;
	inline void Hurt() { m_health -= 5; }
	inline void Health( int health ) { m_health = health; }
	inline int Health() { return m_health; }

private:
	int m_health;
};
