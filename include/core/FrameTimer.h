#include <chrono>

namespace Rasterizer::Core
{
	class FrameTimer
	{
	private:
		std::chrono::steady_clock::time_point m_previous;
	public:
		FrameTimer();
		float Mark();
	};
}
