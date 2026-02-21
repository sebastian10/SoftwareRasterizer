
#include "Engine.h"
#include <random>

namespace Rasterizer::Core
{
	Engine::Engine( MainWindow& m_wnd )
		:
		m_wnd( m_wnd ),
		m_renderer( m_wnd.GetHandle() ),
		ft(),
		//model( "../assets/diablo3_pose.obj" )
		model( "../assets/african_head.obj" )
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
		model.Rotation.x() += 0.1f;
	}

	void Engine::DrawFrame()
	{
		//m_renderer.DrawWireframe( model, Colors::Red );

		//m_renderer.DrawTriangleScanline( Vei2( 7, 45 ), Vei2( 35, 100 ), Vei2( 45, 60 ), Colors::Red );
		//m_renderer.DrawTriangleScanline( Vei2( 120, 35 ), Vei2( 90, 5 ), Vei2( 45, 110 ), Colors::White );
		//m_renderer.DrawTriangleScanline( Vei2( 115, 83 ), Vei2( 80, 90 ), Vei2( 85, 120 ), Colors::Green );

		//int halfWidth = m_renderer.ScreenWidth / 2;

		//Vei3 a( halfWidth, 50, 0 );
		//Vei3 b( 100, m_renderer.ScreenHeight - 100, 100);
		//Vei3 c( m_renderer.ScreenWidth - 100, m_renderer.ScreenHeight - 100, 200 );

		//m_renderer.DrawTriangle( a, b, c, Colors::Red );

		//m_renderer.DrawTriangle( Vector2( 120.0f, 35.0f ), Vector2( 90.0f, 5.0f ), Vector2( 45.0f, 110.0f ), Colors::White );
		//m_renderer.DrawTriangle( Vector2( 115.0f, 83.0f ), Vector2( 80.0f, 90.0f ), Vector2( 85.0f, 120.0f ), Colors::Green );

		m_renderer.DrawModel( model, Colors::Red );
		m_renderer.VisualizeDepth();
	}
}
