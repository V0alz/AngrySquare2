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
			break;
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
	m_gfx->Destroy();
	if( m_gfx != nullptr )
		delete m_gfx;

	Stop();
}
