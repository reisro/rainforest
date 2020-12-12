#include "System/rfApplicationWindow.h"

rfApplicationWindow::rfApplicationWindow()
{
}

rfWindow* rfApplicationWindow::Create()
{
    rfWindow* instanceWindow = new rfWindowWin32();

    return instanceWindow;
}

bool rfApplicationWindow::WindowInitialized()
{
    return false;
}
