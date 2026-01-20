#pragma once

#include <functional>
#include "../../maths/Vector2.h"

namespace Rasterizer::Graphics::Shapes
{
	class Rectangle
	{
	public:
	private:
		int m_top, m_right, m_bottom, m_left;
	public:
		Rectangle( int top, int right, int bottom, int left ) 
			:
			m_top(top), m_right(right), m_bottom(bottom), m_left(left)
		{}
	private:
	};
}