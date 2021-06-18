#include "System/Platform/Windows/rfWindowSystemWin32.h"

rfWindowSystemWin32::rfWindowSystemWin32()
{
    hWnd = 0;

    windowWin32 = new rfWindowWin32();
}

rfWindowSystemWin32::~rfWindowSystemWin32()
{
}

HWND rfWindowSystemWin32::Window()
{
    return windowWin32->GetWindow();
}

bool rfWindowSystemWin32::Initialized()
{
    return windowWin32->initialized;
}
