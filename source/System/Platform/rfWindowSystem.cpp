#include "System/Platform/rfWindowSystem.h"
#include "System/rfApplication.h"

void rfWindowSystem::CreateInstance()
{
    if (rfApplication::GetEngineConfig().platform == EngineConfig::Platform::Windows)
    {
        Singleton = new rfWindowSystemWin32();
        CreateRFWindow();
    }
        
    initialized = true;
}

void rfWindowSystem::CreateRFWindow()
{
    rfWindow::CreateInstance();
}

rfWindowSystem* rfWindowSystem::GetInstance()
{
    return Singleton;
}

HWND rfWindowSystem::Window()
{
    return nullptr;
}
