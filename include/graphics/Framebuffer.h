#pragma once

#include "MainWindow.h"
#include "Color.h"
#include "Vector.h"
#include "Depthbuffer.h"
#include "Matrix.h"

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
		Mat4 ViewportMatrix;
	private:
		HWND m_hWnd;
		ENGINE_BITMAP m_backBuffer;
	public:
		Framebuffer( const HWND& hWnd );
		Framebuffer( const Framebuffer& ) = delete;
		Framebuffer& operator=( const Framebuffer& ) = delete;
		~Framebuffer();
		void Flush();
		void Display();
		void PutPixel( int x, int y, Color c );
	private:
		void ComputeViewportMatrix( const int x, const int y, const int width, const int height );
	};
}
