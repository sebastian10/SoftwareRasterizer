
#include "graphics/Renderer.h"

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
}