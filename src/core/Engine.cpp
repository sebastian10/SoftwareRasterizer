
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
		//m_renderer.DrawWireframe( model, Colors::Red );

		/*m_renderer.DrawTriangleScanline( Vector2Int( 7, 45 ), Vector2Int( 35, 100 ), Vector2Int( 45, 60 ), Colors::Red );
		m_renderer.DrawTriangleScanline( Vector2Int( 120, 35 ), Vector2Int( 90, 5 ), Vector2Int( 45, 110 ), Colors::White );
		m_renderer.DrawTriangleScanline( Vector2Int( 115, 83 ), Vector2Int( 80, 90 ), Vector2Int( 85, 120 ), Colors::Green );*/

		m_renderer.DrawTriangle( Vector2Int( 7, 45 ), Vector2Int( 35, 100 ), Vector2Int( 45, 60 ), Colors::Red );
		m_renderer.DrawTriangle( Vector2Int( 120, 35 ), Vector2Int( 90, 5 ), Vector2Int( 45, 110 ), Colors::White );
		m_renderer.DrawTriangle( Vector2Int( 115, 83 ), Vector2Int( 80, 90 ), Vector2Int( 85, 120 ), Colors::Green );
	}
}
