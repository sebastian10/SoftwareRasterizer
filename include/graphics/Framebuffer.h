#pragma once

#include "MainWindow.h"
#include "Color.h"
#include "Vector2.h"

namespace Rasterizer::Graphics
{
	struct ENGINE_BITMAP
	{
		BITMAPINFO	BitmapInfo;
		Color*		Memory;
	};

	class Framebuffer
	{
	public:
		static constexpr int ScreenWidth = 800;
		static constexpr int ScreenHeight = 600;
	private:
		HWND m_hWnd;
		ENGINE_BITMAP m_backBuffer;
	public:
		Framebuffer( const HWND& hWnd );
		Framebuffer( const Framebuffer& ) = delete;
		Framebuffer& operator=( const Framebuffer& ) = delete;
		~Framebuffer();
		void BeginFrame();
		void EndFrame();
		void PutPixel( int x, int y, Color c );
		void DrawLine( Vector2Int start, Vector2Int end, const Color colour );
		void DrawLine( Vector2 start, Vector2 end, const Color colour )
		{
			DrawLine( Vector2Int( start ), Vector2Int( end ), colour );
		}
	private:
	};
}
