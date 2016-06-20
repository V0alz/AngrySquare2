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
#include "Game.hpp"
#include "System/Input.hpp"
#include "SquarePlayer.hpp"
#include "Graphics\Camera.hpp"
#include "Graphics\Loader\BMP.hpp"

Game::Game()
{
	square = new SquarePlayer();
	apple = new AppleObject( new Sprite( glm::vec2( 0.25f, 0.25f ), BMP::Load( "./res/tex/apple.bmp" ) ) );

	score = 0;
}

Game::~Game()
{
	if( square != nullptr )
		delete square;
	if( apple != nullptr )
		delete apple;
}

void Game::Logic()
{
	square->Update();
	apple->Update();
}

void Game::Frame( Graphics& gfx )
{
	gfx.RequestShader( 0 );
	square->Render( *gfx.GetShader( 0 ) );
	apple->Draw( *gfx.GetShader( 0 ) );
	
	gfx.RequestShader( 1 );
	Text::Render( "Angry Square 2 - Copyright(C) Dennis Walsh.", -2.97f, -2.97f, 0.003f );

	// There must be a better way to do this
	std::stringstream scorestr;
	scorestr << "Score: ";
	scorestr.put( score );

	Text::Render( scorestr.str(), -2.95f, 2.7f, 0.005f );
	score++;
}

/* Notes for settings stuff:
*
*	++ FOR USE WHEN MENU SYSTEM CREATED
*	++ make settings load before menu ideas are started
*
*	- Possible filename: settings.gd
*	- Frame limit
*	- Window dimensions
*	- Fullscreen
*	- VSync
*	- Controls
*	- Sound
*/
