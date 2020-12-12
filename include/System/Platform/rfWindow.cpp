#include "rfWindow.h"
#include "System/rfApplication.h"

void rfWindow::CreateInstance()
{
	if (rfApplication::GetEngineConfig().platform == EngineConfig::Platform::Windows)
		Singleton = new rfWindowWin32();
}
