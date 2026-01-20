
#include "graphics/Renderer.h"
#include "graphics/shapes/Rectangle.h"
#include <assert.h>
#include <algorithm>

namespace Rasterizer::Graphics
{
	Renderer::Renderer( const HWND& hWnd )
		:
		m_framebuffer( hWnd )
	{

	}

	void Renderer::BeginFrame()
	{
		m_framebuffer.Flush();
	}

	void Renderer::EndFrame()
	{
		m_framebuffer.Display();
	}

	void Renderer::DrawLine( Vector2Int start, Vector2Int end, const Color colour )
	{
		bool steep = std::abs( start.x - end.x ) < std::abs( start.y - end.y );
		// transpose the image for steep lines
		if ( steep )
		{
			std::swap( start.x, start.y );
			std::swap( end.x, end.y );
		}

		// make it left-to-right
		if ( start.x > end.x )
		{
			std::swap( start, end );
		}

		int y = start.y;
		int ierror = 0;

		for ( int x = (int) start.x; x <= end.x; x++ )
		{
			// if transposed: de-transpose
			if ( steep )
			{
				m_framebuffer.PutPixel( y, x, colour );
			}
			else
			{
				m_framebuffer.PutPixel( x, y, colour );
			}

			ierror += 2 * std::abs( end.y - start.y );
			if ( ierror > ( end.x - start.x ) )
			{
				y += end.y > start.y ? 1 : -1;
				ierror -= 2 * ( end.x - start.x );
			}
		}
	}

	void Renderer::DrawTriangleWireframe( Vector2Int a, Vector2Int b, Vector2Int c, const Color colour )
	{
		DrawLine( a, b, colour );
		DrawLine( b, c, colour );
		DrawLine( c, a, colour );
	}

	// Scanline rasterization
	void Renderer::DrawTriangleScanline( Vector2Int a, Vector2Int b, Vector2Int c, const Color colour )
	{
		if ( a.y > b.y ) std::swap( a, b );
		if ( a.y > c.y ) std::swap( a, c );
		if ( b.y > c.y ) std::swap( b, c );

		assert( a.y <= b.y && b.y <= c.y );

		// Loop line by line
		for ( int y = a.y; y <= c.y; y++ )
		{
			int x_short;
			// Top half or bottom half
			if ( y < b.y )
				x_short = Intersect( a, b, y );
			else
				x_short = Intersect( b, c, y );

			int x_long = Intersect( a, c, y );

			int x_start = min( x_short, x_long );
			int x_end = max( x_short, x_long );

			for ( int x = x_start; x <= x_end; x++ )
			{
				m_framebuffer.PutPixel( x, y, colour );
			}
		}
	}

	void Renderer::DrawTriangle( Vector2Int a, Vector2Int b, Vector2Int c, const Color colour )
	{
		int top = min( min( a.y, b.y ), c.y );
		int bottom = max( max( a.y, b.y ), c.y );
		int left = min( min( a.x, b.x ), c.x );
		int right = max( max( a.x, b.x ), c.x );

		Shapes::Rectangle boundingRect( top, right, bottom, left );

		for ( int y = top; y < bottom; y++ )
		{
			for ( int x = left; x < right; x++ )
			{
				m_framebuffer.PutPixel( x, y, colour );
			}
		}
	}

	void Renderer::DrawWireframe( const Model& model, const Color colour )
	{
		for ( int i = 0; i < model.FaceCount(); i++ )
		{
			for ( int point = 0; point < 3; point++ )
			{
				Vector2Int start( Project( model.GetVertex( i, point ) ) );
				Vector2Int end = {};

				if ( point == 2 )
				{
					end = Vector2Int( Project( model.GetVertex( i, 0 ) ) );
				}
				else
				{
					end = Vector2Int( Project( model.GetVertex( i, point + 1 ) ) );
				}

				DrawLine( start, end, colour );
			}
		}

		for ( int i = 0; i < model.VertexCount(); i++ )
		{
			Vector2Int vertex = Project( model.GetVertex( i ) );
			m_framebuffer.PutPixel( vertex.x, vertex.y, Colors::White );
		}
	}

	Vector2Int Renderer::Project( const Vector3& v ) const
	{
		// from [-1, 1], to [0, ScreenWidth/ScreenHeight)
		int x = (int) ( ( v.x + 1.0f ) * 0.5f * ( ScreenWidth - 1 ) );
		int y = (int) ( ( v.y + 1.0f ) * 0.5f * ( ScreenHeight - 1 ) );

		// std::cout << "Original: " << v.x << ", " << v.y << " Projection: " << x << ", " << y << std::endl;

		// ScreenHeight - y because of inverted y direction
		return Vector2Int( x, ScreenHeight - 1 - y );
	}

	int Renderer::Intersect( Vector2Int v0, Vector2Int v1, int step ) const
	{
		float t = (float)( step - v0.y ) / ( v1.y - v0.y ); // [0,1]
		float x = v0.x + t * ( v1.x - v0.x );

		return (int)x;
	}
}