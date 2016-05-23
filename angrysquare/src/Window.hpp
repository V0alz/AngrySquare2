#pragma once

#include <GLFW\glfw3.h>
#include "WindowsSettings.hpp"

class Window
{
public:
	static int Create( WindowSettings* settings );
	static void Destroy();
	static void Clear();
	static void SwapBuffers();
	static bool ShouldExit();

private:
	static GLFWwindow* m_window;
};
