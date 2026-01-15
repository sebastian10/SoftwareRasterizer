#pragma once

#include "MainWindow.h"
#include "Framebuffer.h"
#include "Model.h"

namespace Rasterizer::Graphics
{
	class Renderer
	{
	public:
		static constexpr int ScreenWidth = 1200;
		static constexpr int ScreenHeight = 800;
	private:
		Framebuffer m_framebuffer;
	public:
		Renderer( const HWND& hWnd );
		void BeginFrame();
		void EndFrame();
		// Drawing
		void DrawLine( Vector2Int start, Vector2Int end, const Color colour );
		void DrawLine( Vector2 start, Vector2 end, const Color colour )
		{
			DrawLine( Vector2Int( start ), Vector2Int( end ), colour );
		}

		void DrawWireframe( const Model& model, const Color colour );
	private:
		Vector2Int Project ( const Vector3& v ) const;
	};
}