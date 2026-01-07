#include "FrameTimer.h"

using namespace std::chrono;

namespace Rasterizer::Core
{
	FrameTimer::FrameTimer()
	{
		m_previous = steady_clock::now();
	}

	float FrameTimer::Mark()
	{
		time_point old = m_previous;
		m_previous = steady_clock::now();
		duration<float> elapsed = m_previous - old;
		return elapsed.count();
	}
}
