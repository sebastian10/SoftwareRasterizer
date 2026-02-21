
#include "Framebuffer.h"
#include "Renderer.h"
#include <assert.h>

namespace Rasterizer::Graphics
{
	Framebuffer::Framebuffer( const HWND& hWnd )
		:
		m_hWnd( hWnd )
	{
		m_backBuffer.BitmapInfo.bmiHeader.biSize = sizeof( m_backBuffer.BitmapInfo.bmiHeader );
		m_backBuffer.BitmapInfo.bmiHeader.biWidth = Renderer::ScreenWidth;
		m_backBuffer.BitmapInfo.bmiHeader.biHeight = -Renderer::ScreenHeight; // negative so it's not upside down
		m_backBuffer.BitmapInfo.bmiHeader.biPlanes = 1;
		m_backBuffer.BitmapInfo.bmiHeader.biBitCount = 32;
		m_backBuffer.BitmapInfo.bmiHeader.biCompression = BI_RGB;

		// allocate memory for buffer (16-byte aligned for faster access)
		m_backBuffer.Memory = reinterpret_cast<Color*>(
			_aligned_malloc( sizeof( Color ) * Renderer::ScreenWidth * Renderer::ScreenHeight, 16u ) );

		ComputeViewportMatrix( 0, 0, Renderer::ScreenWidth, Renderer::ScreenHeight );
	}

	Framebuffer::~Framebuffer()
	{
		if ( m_backBuffer.Memory )
		{
			_aligned_free( m_backBuffer.Memory );
			m_backBuffer.Memory = nullptr;
		}
	}

	void Framebuffer::Flush()
	{
		memset( m_backBuffer.Memory, 0u, sizeof( Color ) * Renderer::ScreenHeight * Renderer::ScreenWidth );
	}

	void Framebuffer::Display()
	{
		HDC deviceContext = GetDC( m_hWnd );

		StretchDIBits(
			deviceContext,
			0, 0, Renderer::ScreenWidth, Renderer::ScreenHeight,
			0, 0, Renderer::ScreenWidth, Renderer::ScreenHeight,
			m_backBuffer.Memory, &m_backBuffer.BitmapInfo, DIB_RGB_COLORS, SRCCOPY );

		ReleaseDC( m_hWnd, deviceContext );
	}

	void Framebuffer::PutPixel( int x, int y, Color c )
	{
		assert( x >= 0 );
		assert( x < Renderer::ScreenWidth );
		assert( y >= 0 );
		assert( y < Renderer::ScreenHeight );
		m_backBuffer.Memory[y * Renderer::ScreenWidth + x] = c;
	}

	void Framebuffer::ComputeViewportMatrix( const int x, const int y, const int width, const int height )
	{
		const float halfWidth = width / 2.0f;
		const float halfHeight = height / 2.0f;

		ViewportMatrix = {
			halfWidth, 0, 0, x + halfWidth,
			0, halfHeight, 0, y + halfHeight,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}
}
