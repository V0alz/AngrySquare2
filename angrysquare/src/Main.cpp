#include <Windows.h>
#include "System.hpp"
#include <iostream>

int main()
{
	System* sys = new System();
	sys->Start( true );
	delete sys;
	return 0;
}

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	UNREFERENCED_PARAMETER( nCmdShow );
	UNREFERENCED_PARAMETER( lpCmdLine );
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( hInstance );

	System* sys = new System();
	sys->Start( true );
	delete sys;
	return 0;
}
