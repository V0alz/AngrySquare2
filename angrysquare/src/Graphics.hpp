#pragma once

#include "Window.hpp"

class Graphics
{
public:
	Graphics();
	virtual ~Graphics();
	bool InitGL();
	void Destroy();

private:
	bool m_isReady;
};
