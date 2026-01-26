
#include <algorithm>

#include "graphics/Depthbuffer.h"

namespace Rasterizer::Graphics
{
	Depthbuffer::Depthbuffer( int width, int height )
		:
		m_width(width),
		m_height(height),
		m_buffer( width * height )
	{
		Clear( 0 );
	}

	void Depthbuffer::Clear( unsigned char value )
	{
		std::fill( m_buffer.begin(), m_buffer.end(), value );
	}

	void Depthbuffer::Set( int x, int y, unsigned char value )
	{
		m_buffer[y * m_width + x] = value;
	}

	unsigned char Depthbuffer::Get( int x, int y ) const
	{
		return m_buffer[y * m_width + x];
	}

	int Depthbuffer::GetWidth() const
	{
		return m_width;
	}

	int Depthbuffer::GetHeigth() const
	{
		return m_height;
	}
}