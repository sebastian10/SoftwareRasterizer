#pragma once

#ifndef UNICODE
#define UNICODE
#endif 

#include <Windows.h>
#include <iostream>
#include <string>

#include "../include/Graphics.h"

class MainWindow
{
public:
	
private:
	static constexpr wchar_t CLASS_NAME[] = L"Rasterizer Window Class";
	HINSTANCE m_hInst = nullptr;
	HWND m_hWnd = nullptr;
	HWND m_consoleWindow = nullptr;
public:
	MainWindow( HINSTANCE hInstance );
	MainWindow( const MainWindow& ) = delete;
	MainWindow& operator=( const MainWindow& ) = delete;
	~MainWindow();
	HWND GetHandle();
	void ShowMessageBox( const std::wstring& title, const std::wstring& message ) const;
	bool ProcessMessage();
private:
	void AttachDebugConsole();
	void DetachDebugConsole();
	static LRESULT CALLBACK WindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );
};