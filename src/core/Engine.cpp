
#include "Engine.h"

namespace Rasterizer::Core
{
	Engine::Engine( MainWindow& wnd )
		:
		wnd( wnd ),
		framebuffer( wnd.GetHandle() )
	{

	}

	void Engine::Start()
	{
		framebuffer.BeginFrame();
		Update();
		DrawFrame();
		framebuffer.EndFrame();
	}

	void Engine::Update()
	{

	}

	void Engine::DrawFrame()
	{
		int ax = 7, ay = 3;
		int bx = 120, by = 370;
		int cx = 620, cy = 530;

		Vector2 a( 7, 3 );
		Vector2 b( 120, 370 );
		Vector2 c( 620, 530 );

		framebuffer.DrawLine( a, b, Colors::Blue );
		framebuffer.DrawLine( c, b, Colors::Green );
		framebuffer.DrawLine( c, a, Colors::Yellow );
		framebuffer.DrawLine( a, c, Colors::Red );
	}
}
