// Rasterizer.cpp : Defines the entry point for the application.
//

#include "../include/MainWindow.h"
#include "../include/Engine.h"

#include "../_testing/tests/Vector2_test.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, INT )
{
	MainWindow wnd( hInstance );

	Testing::TestRunner runner;
	runner.AddTest( "Constructor test", Testing::Tests::Vector2_test::Constructor_test );
	runner.AddTest( "Addition test", Testing::Tests::Vector2_test::Addition_Test );
	runner.AddTest( "Subtraction test", Testing::Tests::Vector2_test::Subtraction_Test );
	runner.AddTest( "Scalar multiplication test", Testing::Tests::Vector2_test::ScalarMultiplication_Test );
	runner.AddTest( "Length test", Testing::Tests::Vector2_test::Length_Test );
	runner.AddTest( "Normalisation test", Testing::Tests::Vector2_test::Normalisation_Test );

	runner.RunAll();

	Engine engine( wnd );
	while ( wnd.ProcessMessage() )
	{
		engine.Go();
	}

	return 0;
}
