#pragma once

#include "MainWindow.h"
#include "Color.h"

struct ENGINE_BITMAP
{
	BITMAPINFO	BitmapInfo;
	Color*		Memory;
};

class Graphics
{
public:
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
private:
	HWND m_hWnd;
	ENGINE_BITMAP m_backBuffer;
public:
	Graphics( const HWND& hWnd );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	~Graphics();
	void BeginFrame();
	void EndFrame();
	void PutPixel( int x, int y, Color c );
private:
};