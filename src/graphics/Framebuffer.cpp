
#include "Framebuffer.h"
#include <assert.h>

namespace Rasterizer::Graphics
{
	Framebuffer::Framebuffer( const HWND& hWnd )
		:
		m_hWnd( hWnd )
	{
		m_backBuffer.BitmapInfo.bmiHeader.biSize = sizeof( m_backBuffer.BitmapInfo.bmiHeader );
		m_backBuffer.BitmapInfo.bmiHeader.biWidth = Framebuffer::ScreenWidth;
		m_backBuffer.BitmapInfo.bmiHeader.biHeight = -Framebuffer::ScreenHeight; // negative so it's not upside down
		m_backBuffer.BitmapInfo.bmiHeader.biPlanes = 1;
		m_backBuffer.BitmapInfo.bmiHeader.biBitCount = 32;
		m_backBuffer.BitmapInfo.bmiHeader.biCompression = BI_RGB;

		// allocate memory for buffer (16-byte aligned for faster access)
		m_backBuffer.Memory = reinterpret_cast<Color*>(
			_aligned_malloc( sizeof( Color ) * Framebuffer::ScreenWidth * Framebuffer::ScreenHeight, 16u ) );
	}

	Framebuffer::~Framebuffer()
	{
		if ( m_backBuffer.Memory )
		{
			_aligned_free( m_backBuffer.Memory );
			m_backBuffer.Memory = nullptr;
		}
	}

	void Framebuffer::BeginFrame()
	{
		memset( m_backBuffer.Memory, 0u, sizeof( Color ) * Framebuffer::ScreenHeight * Framebuffer::ScreenWidth );
	}

	void Framebuffer::EndFrame()
	{
		HDC deviceContext = GetDC( m_hWnd );

		StretchDIBits(
			deviceContext,
			0, 0, Framebuffer::ScreenWidth, Framebuffer::ScreenHeight,
			0, 0, Framebuffer::ScreenWidth, Framebuffer::ScreenHeight,
			m_backBuffer.Memory, &m_backBuffer.BitmapInfo, DIB_RGB_COLORS, SRCCOPY );

		ReleaseDC( m_hWnd, deviceContext );
	}

	void Framebuffer::PutPixel( int x, int y, Color c )
	{
		assert( x >= 0 );
		assert( x < Framebuffer::ScreenWidth );
		assert( y >= 0 );
		assert( y < Framebuffer::ScreenHeight );
		m_backBuffer.Memory[y * Framebuffer::ScreenWidth + x] = c;
	}

	void Framebuffer::DrawLine( Vector2 start, Vector2 end, const Color colour )
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
		for ( int x = (int)start.x; x <= end.x; x++ )
		{
			float t = ( x - start.x ) / static_cast<float>( end.x - start.x );
			int y = (int) std::round( start.y + t * ( end.y - start.y ) );

			// if transposed: de-transpose
			if ( steep )
			{
				PutPixel( y, x, colour );
			}
			else
			{
				PutPixel( x, y, colour );
			}
		}

		//for ( float t = 0; t < 1; t+=0.001f )
		//{
		//	int x = (int)std::round( start.x + t * ( end.x - start.x ) );
		//	int y = (int)std::round( start.y + t * ( end.y - start.y ) );
		//	PutPixel( x, y, colour );
		//}
	}
}
