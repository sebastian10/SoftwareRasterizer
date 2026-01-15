
#include "Engine.h"
#include <random>

namespace Rasterizer::Core
{
	Engine::Engine( MainWindow& m_wnd )
		:
		m_wnd( m_wnd ),
		m_renderer( m_wnd.GetHandle() ),
		ft(),
		model( "../assets/diablo3_pose.obj" )
		//model( "../assets/african_head.obj" )
	{

	}

	void Engine::Start()
	{
		m_renderer.BeginFrame();
		Update();
		DrawFrame();
		m_renderer.EndFrame();
	}

	void Engine::Update()
	{

	}

	void Engine::DrawFrame()
	{
		m_renderer.DrawWireframe( model, Colors::Red );
		/*int ax = 7, ay = 3;
		int bx = 120, by = 370;
		int cx = 620, cy = 530;

		Vector2 a( 7, 3 );
		Vector2 b( 120, 370 );
		Vector2 c( 620, 530 );

		m_renderer.DrawLine( a, b, Colors::Blue );
		m_renderer.DrawLine( c, b, Colors::Green );
		m_renderer.DrawLine( c, a, Colors::Yellow );
		m_renderer.DrawLine( a, c, Colors::Red );*/


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
