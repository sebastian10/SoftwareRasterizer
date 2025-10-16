// Rasterizer.cpp : Defines the entry point for the application.
//

#include "../include/MainWindow.h"
#include "../include/Engine.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, INT )
{
	MainWindow wnd( hInstance );

	Engine engine( wnd );
	while ( wnd.ProcessMessage() )
	{
		engine.Go();
	}

	return 0;
}
