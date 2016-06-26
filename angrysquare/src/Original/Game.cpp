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
#include "..\Graphics\Camera.hpp"
#include "..\Graphics\Loader\BMP.hpp"
#include "..\System/Input.hpp"

#define _DEBUG_EXTRAS

Game::Game()
{
	square = new SquarePlayer();
	enemy = new SquareEnemy();
	apple = new AppleObject( new Sprite( glm::vec2( 0.25f, 0.25f ), BMP::Load( "./res/tex/apple.bmp" ) ) );

	score = 0;
}

Game::~Game()
{
	std::cout << "Deleting game" << std::endl;
	if( square != nullptr )
		delete square;
	if( apple != nullptr )
		delete apple;
	if( enemy != nullptr )
		delete enemy;
}

void Game::Logic()
{
	square->Update();
	enemy->SetTarget( glm::vec2( square->Position() ) );
	apple->Update();
	enemy->Update();

	if( AABB::Intersects( square->Bounds(), enemy->Bounds() ) )
	{
		square->Hurt();
	}

	if( AABB::Intersects( square->Bounds(), apple->Bounds() ) )
	{
		apple->Respawn();
		score += 5;
	}
}

void Game::Frame( Graphics& gfx )
{
	gfx.RequestShader( 0 );
	square->Render( *gfx.GetShader( 0 ) );
	enemy->Render( *gfx.GetShader( 0 ) );
	apple->Draw( *gfx.GetShader( 0 ) );

	gfx.RequestShader( 1 );

	std::stringstream str;
	str << "Score: ";
	str << score;
	Text::Render( str.str(), -2.95f, 2.7f, 0.005f );

	str.str( std::string() );
	str << "Health: ";
	str << square->Health();
	Text::Render( str.str(), -2.95f, 2.4f, 0.005f );

#ifdef _DEBUG_EXTRAS
	str.str( std::string() );
	str << "Player(X:" << square->Position().x << ", Y: " << square->Position().y << ")";
	Text::Render( str.str(), -2.95f, 1.7f, 0.005f );

	str.str( std::string() );
	str << "Enemy(X:" << enemy->Position().x << ", Y: " << enemy->Position().y << ")";
	Text::Render( str.str(), -2.95f, 1.4f, 0.005f );

	str.str( std::string() );
	str << "Apple(X:" << apple->Transfromation().Position().x << ", Y: " << apple->Transfromation().Position().y << ")";
	Text::Render( str.str(), -2.95f, 1.1f, 0.005f );
#endif
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
