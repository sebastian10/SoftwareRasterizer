#pragma once

#include "Framebuffer.h"
#include "MainWindow.h"
#include "FrameTimer.h"

namespace Rasterizer::Core
{
	class Engine
	{
	public:
		FrameTimer ft;
	private:
		MainWindow& wnd;
		Rasterizer::Graphics::Framebuffer framebuffer;
	public:
		Engine( MainWindow& wnd );
		void Start();
	private:
		void Update();
		void DrawFrame();
	};
}
