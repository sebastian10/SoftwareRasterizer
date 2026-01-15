#pragma once

#include "Framebuffer.h"
#include "MainWindow.h"
#include "Renderer.h"
#include "FrameTimer.h"
#include "graphics/Model.h"

namespace Rasterizer::Core
{
	class Engine
	{
	public:
		FrameTimer ft;
		Rasterizer::Graphics::Model model;
	private:
		MainWindow& m_wnd;
		Rasterizer::Graphics::Renderer m_renderer;
	public:
		Engine( MainWindow& wnd );
		void Start();
	private:
		void Update();
		void DrawFrame();
	};
}
