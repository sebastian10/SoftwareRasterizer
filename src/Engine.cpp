
#include "../include/Engine.h";

Engine::Engine( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd.GetHandle() )
{

}

void Engine::Go()
{
	gfx.BeginFrame();
	Update();
	DrawFrame();
	gfx.EndFrame();
}

void Engine::Update()
{

}

void Engine::DrawFrame()
{
	for ( int x = 0; x < 100; x++ )
	{
		for ( int y = 0; y < 100; y++ )
		{
			gfx.PutPixel( x, y, Color( 255, 0, 255 ) );
		}
	}
}