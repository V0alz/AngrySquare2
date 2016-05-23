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
#include "System.hpp"
#include "SysState.hpp"

System::System()
{
	m_running = false;
	m_gfx = nullptr;
}

System::~System()
{

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
	do
	{
		switch( SysState::Get() )
		{
		case SysState::States::STATE_STARTUP:
		{
			m_gfx = new Graphics();
			if( !m_gfx )
			{
				SysState::Set( SysState::States::STATE_CLEANUP );
			}
			m_gfx->InitGL();
			SysState::Set( SysState::States::STATE_PLAYING );
			break; 
		}
		case SysState::States::STATE_PLAYING:
		{
			Window::Clear();
			if( Window::ShouldExit() )
			{
				SysState::Set( SysState::States::STATE_CLEANUP );
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
		Window::SwapBuffers();
		glfwPollEvents();
	} while( m_running );
}

void System::Clean()
{
	if( m_gfx != nullptr )
	{
		m_gfx->Destroy();
		delete m_gfx;
		m_gfx = nullptr;
	}
	Stop();
}
