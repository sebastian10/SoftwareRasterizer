#pragma once

#include "Framebuffer.h"
#include "MainWindow.h"
#include "Renderer.h"
#include "FrameTimer.h"
#include "graphics/Model.h"

#include "graphics/lighting/DirectionalLight.h"
#include "graphics/lighting/PointLight.h"

using namespace Rasterizer::Graphics::Lighting;

namespace Rasterizer::Core
{
	class Engine
	{
	public:
		FrameTimer ft;
		Rasterizer::Graphics::Model model;
		std::vector<std::unique_ptr<ILight>> lights;
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
