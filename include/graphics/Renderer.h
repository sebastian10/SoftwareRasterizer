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

		/*
		 * Drawing
		*/ 
		void DrawLine( Vector2Int start, Vector2Int end, const Color colour );
		void DrawLine( Vector2 start, Vector2 end, const Color colour )
		{
			DrawLine( Vector2Int( start ), Vector2Int( end ), colour );
		}
		void DrawTriangleWireframe( Vector2Int a, Vector2Int b, Vector2Int c, const Color colour );
		// Scanline rasterization
		void DrawTriangleScanline( Vector2Int a, Vector2Int b, Vector2Int c, const Color colour );
		// Barycentric coordinates
		void DrawTriangle( const Vector3& a, const Vector3& b, const Vector3& c, const Color colour );
		void DrawTriangle( const Vector2Int& a, const Vector2Int& b, const Vector2Int& c, const Color colour );

		// Model
		void DrawWireframe( const Model& model, const Color colour );
		void DrawModel( const Model& model, const Color colour );
	private:
		Vector2Int Project ( const Vector3& v ) const;
		int Intersect ( Vector2Int v0, Vector2Int v1, int step ) const;
	};
}