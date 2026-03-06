
#include "Engine.h"
#include <random>

namespace Rasterizer::Core
{
	Engine::Engine( MainWindow& m_wnd )
		:
		m_wnd( m_wnd ),
		m_renderer( m_wnd.GetHandle() ),
		ft(),
		// this is werde the model gets loaded in, other test model: diablo3_pose.obj
		model( "../assets/african_head.obj" )
	{
		// lights get added here, multiple lights allowed
		// light types: DirectionalLight and PointLight
		lights.emplace_back( std::make_unique<DirectionalLight>( Vec3( 1.0f, -2.0f, -2.0f ), Vec3( 1.0f, 1.0f, 1.0f ), 1.0f ) );
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
		float delta = ft.Mark();

		// update stuff happens here, like rotating the model:
		//model.Rotation.x() = -0.5f;
		model.Rotation.x() += -0.1f * delta;

		// simple fps counter
		std::cout << 1.0f / delta << " FPS" << std::endl;
	}

	void Engine::DrawFrame()
	{
		// m_renderer has some drawing functions:
		// DrawLine, DrawTriangle, DrawWireframe, DrawModel

		//m_renderer.DrawTriangleWireframe( Vei2( 10, 10 ), Vei2( 40, 30 ), Vei2( 5, 50 ), Colors::Cyan );
		//m_renderer.DrawTriangleWireframe( Vei2( 50, 5 ), Vei2( 60, 40 ), Vei2( 40, 50 ), Colors::Red );
		//m_renderer.DrawTriangleWireframe( Vei2( 70, 40 ), Vei2( 90, 20 ), Vei2( 80, 50 ), Colors::Green );

		//m_renderer.DrawWireframe( model, Colors::Red );
		m_renderer.DrawModel( model, Colors::Red, lights );
	}
}
