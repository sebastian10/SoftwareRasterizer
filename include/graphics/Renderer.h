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
		void DrawLine( Vector2Int start, Vector2Int end, const Color colour );
		void DrawLine( Vector2 start, Vector2 end, const Color colour )
		{
			DrawLine( Vector2Int( start ), Vector2Int( end ), colour );
		}
		void DrawTriangleWireframe( Vector2Int a, Vector2Int b, Vector2Int c, const Color colour );
		// Scanline rasterization
		void DrawTriangleScanline( Vector2Int a, Vector2Int b, Vector2Int c, const Color colour );
		// Barycentric coordinates
		void DrawTriangle( const Vector3Int& a, const Vector3Int& b, const Vector3Int& c, const Color colour );

		// Model
		void DrawWireframe( const Model& model, const Color colour );
		void DrawModel( const Model& model, const Color colour );

		void VisualizeDepth();
	private:
		Vector3Int Project ( const Vector3& v ) const;
		int Intersect ( Vector2Int v0, Vector2Int v1, int step ) const;
	};
}