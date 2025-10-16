
#include "../include/MainWindow.h"

MainWindow::MainWindow( HINSTANCE hInstance )
    :
    m_hInst( hInstance )
{
    AttachDebugConsole();

    WNDCLASSEX wc = {};
    wc.cbSize = sizeof( WNDCLASSEX );
    wc.lpfnWndProc = MainWindow::WindowProc;
    wc.hInstance = m_hInst;
    wc.lpszClassName = CLASS_NAME;

    if ( !RegisterClassEx( &wc ) )
    {
        std::cout << "Register class failed! Error: " << GetLastError() << std::endl;
        return;
    }

    m_hWnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Software Rasterizer",         // Window text
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, Graphics::ScreenWidth, Graphics::ScreenHeight,

        NULL,       // Parent window    
        NULL,       // Menu
        m_hInst,    // Instance handle
        this        // Additional application data
    );

    if ( m_hWnd == nullptr )
    {
        std::cout << "Window creation failed! Error: " << GetLastError() << std::endl;
        return;
    }

    ShowWindow( m_hWnd, SW_SHOWDEFAULT );
}

MainWindow::~MainWindow()
{
    UnregisterClass( CLASS_NAME, m_hInst );
}

HWND MainWindow::GetHandle()
{
    return m_hWnd;
}

void MainWindow::ShowMessageBox( const std::wstring& title, const std::wstring& message ) const
{
    MessageBox( m_hWnd, message.c_str(), title.c_str(), MB_OK );
}

bool MainWindow::ProcessMessage()
{
    MSG msg;
    while ( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
        if ( msg.message == WM_QUIT )
        {
            return false;
        }
    }
    return true;
}

void MainWindow::AttachDebugConsole()
{
    // Check if Console already exists
    
    if ( GetConsoleWindow() != nullptr )
        return;
    AllocConsole();

    // Rebind streams to console
    FILE* f;
    freopen_s( &f, "CONOUT$", "w", stdout );
    freopen_s( &f, "CONOUT$", "w", stderr );
    freopen_s( &f, "CONIN$", "r", stdin );
    
    SetConsoleTitle( L"Debug Console" );

    m_consoleWindow = GetConsoleWindow();

    std::cout << "=== Console attached successfully! ===\n";
}

void MainWindow::DetachDebugConsole()
{
    if ( m_consoleWindow )
    {
        std::cout << "=== Console detached! ===\n";
        FreeConsole();
    }
}

LRESULT MainWindow::WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    MainWindow* pThis = nullptr;

    if ( uMsg == WM_NCCREATE )
    {
        // Extract the "this" pointer from lpCreateParams
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>( lParam );
        pThis = reinterpret_cast<MainWindow*>( pCreate->lpCreateParams );
        SetWindowLongPtr( hWnd, GWLP_USERDATA, (LONG_PTR) pThis );

        pThis->m_hWnd = hWnd;
    }
    else
    {
        // Retrieve stored "this" pointer
        pThis = reinterpret_cast<MainWindow*>( GetWindowLongPtr( hWnd, GWLP_USERDATA ) );
    }

    if ( pThis )
    {
        return pThis->HandleMessage( uMsg, wParam, lParam );
    }
    else
    {
        return DefWindowProc( hWnd, uMsg, wParam, wParam );
    }
}

LRESULT MainWindow::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    switch ( uMsg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;

        default:
            return DefWindowProc( m_hWnd, uMsg, wParam, lParam );
    }
}
