
#include "graphics/Renderer.h"
#include "graphics/shapes/Rectangle.h"
#include <assert.h>
#include <algorithm>

#include <random>

namespace Rasterizer::Graphics
{
	Renderer::Renderer( const HWND& hWnd )
		:
		m_framebuffer( hWnd ),
		m_depthbuffer( ScreenWidth, ScreenHeight )
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
				if ( x < 0 || x >= ScreenWidth || y < 0 || y >= ScreenHeight )
					continue;

				m_framebuffer.PutPixel( x, y, colour );
			}
		}
	}

	void Renderer::DrawTriangle( const Vector3Int& a, const Vector3Int& b, const Vector3Int& c, const Color colour )
	{
		int top = min( min( a.y, b.y ), c.y );
		int bottom = max( max( a.y, b.y ), c.y );
		int left = min( min( a.x, b.x ), c.x );
		int right = max( max( a.x, b.x ), c.x );

		auto Edge = []( const Vector3Int& a, const Vector3Int& b, const Vector3Int& p )
		{
			Vector3Int a_int = Vector3Int( a );
			Vector3Int b_int = Vector3Int( b );
			Vector3Int p_int = Vector3Int( p );

			return ( b_int - a_int ).Cross( p_int - a_int ).z;
		};

		int area = Edge( a, b, c );
		if ( area >= 0 ) // positive area pointing backwards
			return;

		#pragma omp parallel for
		for ( int y = top; y < bottom; y++ )
		{
			for ( int x = left; x < right; x++ )
			{
				Vector2Int p( x, y );
				float alpha = (float) Edge( a, b, p ) / area;
				float beta = (float) Edge( b, c, p ) / area;
				float gamma = (float) Edge( c, a, p ) / area;

				if ( alpha < 0 || beta < 0 || gamma < 0 )
					continue;
				
				unsigned char depth = static_cast<unsigned char>( alpha * a.z + beta * b.z + gamma * c.z );

				if ( depth <= m_depthbuffer.Get( x, y ) )
					continue;

				m_depthbuffer.Set( x, y, depth );
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
				Vector3Int start( Project( model.GetVertex( i, point ) ) );
				Vector3Int end = {};

				if ( point == 2 )
				{
					end = Vector3Int( Project( model.GetVertex( i, 0 ) ) );
				}
				else
				{
					end = Vector3Int( Project( model.GetVertex( i, point + 1 ) ) );
				}

				DrawLine( Vector2Int( start.x, start.y ), Vector2Int( end.x, end.y ), colour );
			}
		}

		for ( int i = 0; i < model.VertexCount(); i++ )
		{
			Vector3Int vertex = Project( model.GetVertex( i ) );
			m_framebuffer.PutPixel( vertex.x, vertex.y, Colors::White );
		}
	}

	void Renderer::DrawModel( const Model& model, const Color colour )
	{
		std::mt19937 rng( std::random_device{}() );
		std::uniform_int_distribution<int> colorDist( 0, 255 );

		for ( int i = 0; i < model.FaceCount(); i++ )
		{
			Vector3Int a( Project( model.GetVertex( i, 0 ) ) );
			Vector3Int b( Project( model.GetVertex( i, 1 ) ) );
			Vector3Int c( Project( model.GetVertex( i, 2 ) ) );

			DrawTriangle( a, b, c, Colors::MakeRGB( colorDist( rng ), colorDist( rng ), colorDist( rng ) ) );
			//DrawTriangle( a, b, c, colour );
		}
	}

	Vector3Int Renderer::Project( const Vector3& v ) const
	{
		// from [-1, 1], to [0, ScreenWidth/ScreenHeight)
		float scaleX = ( ScreenWidth - 1 ) * 0.5f;
		float scaleY = ( ScreenHeight - 1 ) * 0.5f;
		float scale = min( scaleX, scaleY );

		float offsetX = ScreenWidth * 0.5f;
		float offsetY = ScreenHeight * 0.5f;

		int x = (int) ( ( v.x ) * scale + offsetX );
		int y = (int) ( ( v.y ) * scale + offsetY );
		int z = (int) ( ( v.z + 1.0f ) * 255 * 0.5f ); // mapped to [0,255]

		// std::cout << "Original: " << v.x << ", " << v.y << " Projection: " << x << ", " << y << std::endl;

		// ScreenHeight - y because of inverted y direction
		return Vector3Int( x, ScreenHeight - 1 - y, z );
	}

	int Renderer::Intersect( Vector2Int v0, Vector2Int v1, int step ) const
	{
		float t = (float)( step - v0.y ) / ( v1.y - v0.y ); // [0,1]
		float x = v0.x + t * ( v1.x - v0.x );

		return (int)x;
	}

	void Renderer::VisualizeDepth()
	{
		for ( int y = 0; y < m_depthbuffer.GetHeigth(); y++ )
		{
			for ( int x = 0; x < m_depthbuffer.GetWidth(); x++ )
			{
				m_framebuffer.PutPixel( x, y, Colors::Grayscale( m_depthbuffer.Get( x, y ) ) );
			}
		}

		
	}
}