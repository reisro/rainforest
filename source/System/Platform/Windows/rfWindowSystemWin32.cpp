#include "System/Platform/Windows/rfWindowSystemWin32.h"

rfWindowSystemWin32::rfWindowSystemWin32()
{
}

rfWindowSystemWin32::~rfWindowSystemWin32()
{
}

HWND rfWindowSystemWin32::Window()
{
    return window->GetWindow();
}
