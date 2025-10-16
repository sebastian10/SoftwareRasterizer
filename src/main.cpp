// Rasterizer.cpp : Defines the entry point for the application.
//

#include "../include/MainWindow.h"
#include "../include/Engine.h"

#include "../testing/TestRunner.h"
#include "../testing/tests/Vector2_test.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, INT )
{
	MainWindow wnd( hInstance );

	TestRunner runner;
	runner.AddTest( "Constructor test", Vector2_test::Constructor_test );
	runner.RunAll();

	Engine engine( wnd );
	while ( wnd.ProcessMessage() )
	{
		engine.Go();
	}

	return 0;
}
