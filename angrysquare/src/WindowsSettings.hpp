#pragma once

struct WindowSettings
{
	int m_width;
	int m_height;
	bool m_fullscreen;

	WindowSettings( bool loadSaved = false )
	{
		// Default window settings incase none are provided.
		// Remove default constructor in future.
		if( !loadSaved )
		{
			m_width = 800;
			m_height = 600;
			m_fullscreen = false;
		}
		else
		{
			// load saved data
		}
	}
};
