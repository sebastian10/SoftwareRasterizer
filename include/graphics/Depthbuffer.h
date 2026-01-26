#pragma once

#include <vector>

namespace Rasterizer::Graphics
{
	class Depthbuffer
	{
	public:
	private:
		std::vector<unsigned char> m_buffer;
		int m_width, m_height;
	public:
		Depthbuffer( const int width, const int height );
		void Clear( unsigned char value );
		void Set( int x, int y, unsigned char value );
		unsigned char Get( int x, int y ) const;
		int GetWidth() const;
		int GetHeigth() const;
	private:
	};
}