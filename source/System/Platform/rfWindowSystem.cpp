#include "System/Platform/rfWindowSystem.h"
#include "System/rfConfig.h"
#include "System/rfApplication.h"

static rfWindowSystem* Singleton = 0;
static bool	windowInitialized = false;

void rfWindowSystem::CreateInstance()
{
    if (rfConfig::Instance.platform == EngineConfig::Platform::Windows)
        Singleton = new rfWindowSystemWin32();
}

bool rfWindowSystem::Initialized()
{
    return Singleton->Initialized();
}

bool rfWindowSystem::Init()
{
    Singleton->CreateInstance();

    return Singleton?Singleton->Initialized():0;
}

rfWindowSystem* rfWindowSystem::GetInstance()
{
    return static_cast<rfWindowSystem*> (Singleton);
}

HWND rfWindowSystem::Window()
{
    return nullptr;
}
