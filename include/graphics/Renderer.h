#pragma once

#include "MainWindow.h"
#include "Framebuffer.h"
#include "Depthbuffer.h"
#include "Model.h"

// Coordinate conventions:
// - Screen space Y increases downward
// - Front-facing triangles have NEGATIVE signed area
// - Backface culling uses: area >= 0

namespace Rasterizer::Graphics
{
	class Renderer
	{
	public:
		static constexpr int ScreenWidth = 1200;
		static constexpr int ScreenHeight = 800;
	private:
		Framebuffer m_framebuffer;
		Depthbuffer m_depthbuffer;
	public:
		Renderer( const HWND& hWnd );
		void BeginFrame();
		void EndFrame();
		
		/*
		 * Drawing
		*/ 
		void DrawLine( Vei2 start, Vei2 end, const Color colour );
		void DrawLine( Vec2 start, Vec2 end, const Color colour )
		{
			DrawLine( Vei2( start ), Vei2( end ), colour );
		}
		void DrawTriangleWireframe( Vei2 a, Vei2 b, Vei2 c, const Color colour );
		// Scanline rasterization
		void DrawTriangleScanline( Vei2 a, Vei2 b, Vei2 c, const Color colour );
		// Barycentric coordinates
		void DrawTriangle( const Vei3& a, const Vei3& b, const Vei3& c, const Color colour );

		// Model
		void DrawWireframe( const Model& model, const Color colour );
		void DrawModel( const Model& model, const Color colour );

		void VisualizeDepth();
	private:
		Vei3 Project ( const Vec3& v ) const;
		int Intersect ( Vei2 v0, Vei2 v1, int step ) const;
	};
}