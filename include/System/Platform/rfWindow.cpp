#include "rfWindow.h"
#include "System/rfApplication.h"
#include "System/rfConfig.h"

static rfWindow* Singleton;

void rfWindow::CreateInstance()
{
	if (rfConfig::Instance.platform == EngineConfig::Platform::Windows)
		Singleton = new rfWindowWin32();
}

rfWindow* rfWindow::GetInstance()
{
	return Singleton;
}
