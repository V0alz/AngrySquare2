#pragma once

#include "Graphics.hpp"

class System
{
public:
	System();
	~System();
	void Start( bool andRun = true );
protected:
	void Stop();
	void Run();
	void Clean();


private:
	bool m_running;
	Graphics* m_gfx;
};
