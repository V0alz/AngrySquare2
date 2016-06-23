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
#include <iostream>
#include "System.hpp" 
#include "SysState.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include "../Graphics/Camera.hpp"
#include "../Graphics/Loader/GCF.hpp"

SysState::States SysState::m_sysState = SysState::States::STATE_STARTUP;

System::System()
{
	m_running = false;
	m_settings = GCF::Load();
	m_gfx = nullptr;
	m_game = nullptr;
}

System::~System()
{
	Clean();
}

void System::Start( bool andRun )
{
	if( m_running )
	{
		return;
	}

	m_running = true;
	if( andRun )
	{
		Run();
	}
}

void System::Stop()
{
	if( !m_running )
	{
		return;
	}

	m_running = false;
}

void System::Run()
{
	const double frameTime = 1.0 / m_settings.m_fps;
	Time::SetDelta( frameTime );
	Timer lastTime = Time::GetTime();
	double unprocessed = 0;
	double frameTimer = 0;
	int frames = 0;

	bool doRender = false;

	do
	{
		doRender = false;
		Timer startTime = Time::GetTime();
		Timer passedTime = startTime - lastTime;
		lastTime = startTime;

		unprocessed += passedTime;
		frameTimer += passedTime;

		if( frameTimer >= 1.0 )
		{
#ifdef _DEBUG 
			std::cout << frames << " " << passedTime << std::endl;
#endif
			frames = 0;
			frameTimer = 0;
		}

		while( unprocessed > frameTime )
		{
			glfwPollEvents();
			Update();

			doRender = true;

			unprocessed -= frameTime;
		}

		if( doRender )
		{
			Window::Clear();
			Render();
			Window::SwapBuffers();
			frames++;
		}
		else
		{
			Sleep( 1 );
		}
	}
	while( m_running );
}

void System::Clean()
{
	MenuManager::Destroy();
	if( m_game != nullptr )
	{
		delete m_game;
		m_game = nullptr;
	}
	if( m_gfx != nullptr )
	{
		m_gfx->Destroy();
		delete m_gfx;
		m_gfx = nullptr;
	}

	Stop();
}

void System::Update()
{
	if( Window::ShouldExit() )
	{
		SysState::Set( SysState::States::STATE_CLEANUP );
	}

	static Timer paused_last;
	switch( SysState::Get() )
	{
	case SysState::States::STATE_STARTUP:
	{
		m_gfx = new Graphics();
		if( !m_gfx )
		{
			SysState::Set( SysState::States::STATE_CLEANUP );
		}
		m_gfx->InitGL( m_settings );
		Input::Init();
		MenuManager::Init();
		SysState::Set( SysState::States::STATE_MENU );
		break;
	}
	case SysState::States::STATE_MENU:
	{
		MenuManager::Update();
		break;
	}
	case SysState::States::STATE_LOAD:
	{
		m_game = new Game();
		SysState::Set( SysState::States::STATE_PLAYING );
		break;
	}
	case SysState::States::STATE_PLAYING:
	{
		if( Input::Get( GLFW_KEY_ESCAPE ) )
		{
			paused_last = Time::GetTime();
			SysState::Set( SysState::States::STATE_PAUSED );
		}
		m_game->Logic();
		break;
	}
	case SysState::States::STATE_PAUSED:
	{	
		if( Input::Get( GLFW_KEY_SPACE ) )
		{
			SysState::Set( SysState::States::STATE_PLAYING );
		}
		if( Input::Get( GLFW_KEY_ESCAPE ) && ((Time::GetTime() - paused_last) > 0.2f) )
		{
			delete m_game;
			m_game = nullptr;
			SysState::Set( SysState::States::STATE_MENU );
		}
		break;
	}
	case SysState::States::STATE_CLEANUP:
	{
		Clean();
		return;
	}
	default:
		break;
	}
}

void System::Render()
{
	switch( SysState::Get() )
	{
	case SysState::STATE_MENU:
	{
		m_gfx->RequestShader( 1 );
		MenuManager::Render( *m_gfx );
		break;
	}
	case SysState::States::STATE_PAUSED:
	{
		//m_game->Frame( *m_gfx );
		m_gfx->RequestShader( 1 );
		
		Text::Render( "PAUSED", -1.0f, 0.9f, 0.012f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
		Text::Render( "To continue press SPACE", -1.0f, 0.0f, 0.005f );
		Text::Render( "To quit press ESCAPE", -1.0f, 0.35f, 0.005f ); 
		break;
	}
	case SysState::States::STATE_PLAYING:
	{
		m_game->Frame( *m_gfx );
		break;
	}
	default:
	case SysState::States::STATE_CLEANUP:
	case SysState::States::STATE_STARTUP:
		break;
	}
}
