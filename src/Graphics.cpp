
#include "../include/Graphics.h"
#include <assert.h>

Graphics::Graphics( const HWND& hWnd )
	:
	m_hWnd( hWnd )
{
	m_backBuffer.BitmapInfo.bmiHeader.biSize = sizeof( m_backBuffer.BitmapInfo.bmiHeader );
	m_backBuffer.BitmapInfo.bmiHeader.biWidth = Graphics::ScreenWidth;
	m_backBuffer.BitmapInfo.bmiHeader.biHeight = -Graphics::ScreenHeight; // negative so it's not upside down
	m_backBuffer.BitmapInfo.bmiHeader.biPlanes = 1;
	m_backBuffer.BitmapInfo.bmiHeader.biBitCount = 32;
	m_backBuffer.BitmapInfo.bmiHeader.biCompression = BI_RGB;

	// allocate memory for buffer (16-byte aligned for faster access)
	m_backBuffer.Memory = reinterpret_cast<Color*>(
		_aligned_malloc( sizeof( Color ) * Graphics::ScreenWidth * Graphics::ScreenHeight, 16u ) );
}

Graphics::~Graphics()
{
	if ( m_backBuffer.Memory )
	{
		_aligned_free( m_backBuffer.Memory );
		m_backBuffer.Memory = nullptr;
	}
}

void Graphics::BeginFrame()
{
	memset( m_backBuffer.Memory, 0u, sizeof( Color ) * Graphics::ScreenHeight * Graphics::ScreenWidth );
}

void Graphics::EndFrame()
{
	HDC deviceContext = GetDC( m_hWnd );

	StretchDIBits(
		deviceContext,
		0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight,
		0, 0, Graphics::ScreenWidth, Graphics::ScreenHeight,
		m_backBuffer.Memory, &m_backBuffer.BitmapInfo, DIB_RGB_COLORS, SRCCOPY );

	ReleaseDC( m_hWnd, deviceContext );
}

void Graphics::PutPixel( int x, int y, Color c )
{
	assert( x >= 0 );
	assert( x < Graphics::ScreenWidth );
	assert( y >= 0 );
	assert( y < Graphics::ScreenHeight );
	m_backBuffer.Memory[y * Graphics::ScreenWidth + x] = c;
}