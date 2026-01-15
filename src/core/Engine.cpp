
#include "Engine.h"
#include <random>

namespace Rasterizer::Core
{
	Engine::Engine( MainWindow& wnd )
		:
		wnd( wnd ),
		framebuffer( wnd.GetHandle() ),
		ft(),
		model( "../assets/diablo3_pose.obj" )
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


		/*std::mt19937 rng( std::random_device{}( ) );
		std::uniform_int_distribution<int> XDist( 0, Graphics::Framebuffer::ScreenWidth - 1 );
		std::uniform_int_distribution<int> YDist( 0, Graphics::Framebuffer::ScreenHeight - 1 );

		std::uniform_int_distribution<int> ColourDist( 0, 255 );

		ft.Mark();
		for ( int i = 0; i < 1000; i++ )
		{
			framebuffer.DrawLine( Vector2Int( XDist( rng ), YDist( rng ) ), 
				Vector2( XDist( rng ), YDist( rng ) ), 
				Colors::MakeRGB( ColourDist(rng), ColourDist(rng), ColourDist(rng) ) );
		}
		std::cout << ft.Mark();*/


	}
}
