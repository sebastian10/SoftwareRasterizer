#pragma once

#include "Framebuffer.h"
#include "MainWindow.h"

namespace Rasterizer::Core
{
	class Engine
	{
	public:
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
