#include "System/Platform/rfWindowSystem.h"
#include "System/rfApplication.h"

static rfWindowSystem* Singleton;
static bool	windowInitialized = false;

bool rfWindowSystem::Initialized()
{
    return true;
}

void rfWindowSystem::CreateInstance()
{
    if (rfApplication::GetEngineConfig().platform == EngineConfig::Platform::Windows)
    {
        Singleton = new rfWindowSystemWin32();
    }
}

rfWindowSystem* rfWindowSystem::GetInstance()
{
    return Singleton;
}

HWND rfWindowSystem::Window()
{
    return nullptr;
}
