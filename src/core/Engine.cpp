
#include "Engine.h"
#include <random>

namespace Rasterizer::Core
{
	Engine::Engine( MainWindow& m_wnd )
		:
		m_wnd( m_wnd ),
		m_renderer( m_wnd.GetHandle() ),
		ft(),
		// model( "../assets/diablo3_pose.obj" )
		model( "../assets/african_head.obj" )
	{
		lights.emplace_back( std::make_unique<DirectionalLight>( Vec3( 1.0f, -1.0f, -1.0f ), Vec3( 1.0f, 1.0f, 1.0f ), 1.0f ) );
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
		//model.Rotation.x() = -0.5f;
		model.Rotation.x() += -0.1f;
	}

	void Engine::DrawFrame()
	{
		m_renderer.DrawModel( model, Colors::Red, lights );
		//m_renderer.VisualizeDepth();
	}
}
