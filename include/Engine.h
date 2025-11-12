#pragma once

#include "Graphics.h"
#include "MainWindow.h"

class Engine
{
public:
private:
	MainWindow& wnd;
	Graphics gfx;
public:
	Engine( MainWindow& wnd );
	void Start();
private:
	void Update();
	void DrawFrame();
};