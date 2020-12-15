#include "rfWindow.h"
#include "System/rfApplication.h"

static rfWindow* Singleton;

void rfWindow::CreateInstance()
{
	if (rfApplication::GetEngineConfig().platform == EngineConfig::Platform::Windows)
		Singleton = new rfWindowWin32();
}

rfWindow* rfWindow::GetInstance()
{
	return Singleton;
}
