#pragma once

#include "Graphics.h"
#include "MainWindow.h"

namespace Rasterizer::Core
{
	class Engine
	{
	public:
	private:
		MainWindow& wnd;
		Rasterizer::Graphics::Graphics gfx;
	public:
		Engine( MainWindow& wnd );
		void Start();
	private:
		void Update();
		void DrawFrame();
	};
}
