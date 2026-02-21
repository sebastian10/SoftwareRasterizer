#pragma once

#include <vector>

namespace Rasterizer::Graphics
{
	class Depthbuffer
	{
	public:
	private:
		std::vector<double> m_buffer;
		int m_width, m_height;
	public:
		Depthbuffer( const int width, const int height );
		void Clear( double value );
		void Set( int x, int y, double value );
		double Get( int x, int y ) const;
		int GetWidth() const;
		int GetHeigth() const;
	private:
	};
}