#include "System/Platform/rfWindowSystem.h"
#include "System/rfConfig.h"
#include "System/rfApplication.h"

static rfWindowSystem* Singleton;
static bool	windowInitialized = false;

bool rfWindowSystem::Initialized()
{
    return true;
}

void rfSubsystem::CreateInstance()
{
    if (rfConfig::Instance.platform == EngineConfig::Platform::Windows)
    {
        Singleton = new rfWindowSystemWin32();
    }
}

rfWindowSystem* rfWindowSystem::GetInstance()
{
    return static_cast<rfWindowSystem*> (Singleton);
}

HWND rfWindowSystem::Window()
{
    return nullptr;
}
