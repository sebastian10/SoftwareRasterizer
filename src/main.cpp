// Rasterizer.cpp : Defines the entry point for the application.
//

#include "MainWindow.h"
#include "Engine.h"

using Rasterizer::Core::Engine;
using Rasterizer::Core::MainWindow;

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, INT )
{
	MainWindow m_wnd( hInstance );

	Engine engine( m_wnd );
	while ( m_wnd.ProcessMessage() )
	{
		engine.Start();
	}

	return 0;
}
