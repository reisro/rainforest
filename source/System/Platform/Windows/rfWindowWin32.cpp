#include "System/Platform/Windows/rfWindowWin32.h"

rfWindowWin32::rfWindowWin32()
{
    hWnd = NULL;
    wc = {};
    titleName = "Volleyball Court - Rain Forest Engine";
    hInstance = (HINSTANCE)GetModuleHandle(NULL);
    Name = "";
    cmdShow = 10;

    Create();
}

rfWindowWin32::~rfWindowWin32()
{
}

void rfWindowWin32::Create()
{
    CreateWin32Window();
}

void rfWindowWin32::CreateWin32Window()
{
    // Registering the window class
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "WindowTitle";

    RegisterClass(&wc);

    // Creating the window
    hWnd = CreateWindowExA(0, "WindowTitle", titleName, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080, NULL, NULL, hInstance, NULL);

    if (hWnd == NULL)
    {
        MessageBoxA(0, "Failed to create window.", "Fatal Error", MB_OK | MB_ICONEXCLAMATION | MB_APPLMODAL);

        initialized = false;
    }

    ShowWindow(hWnd, cmdShow);
    ::UpdateWindow(hWnd);

    RFGE_LOG("Window created.");

    initialized = true;
}

void rfWindowWin32::Close()
{
}

HWND rfWindowWin32::GetWindow()
{
    return hWnd;
}

LRESULT rfWindowWin32::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
        }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}