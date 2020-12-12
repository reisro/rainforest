
//---------------------------------------------------------------------------//
//                                                                           //
// File : main.cpp                                                           //
//                                                                           //
// Desc : Template game entry point									         //
//                                                                           //
//                                                                           //
//---------------------------------------------------------------------------//
//     Rain Forest game engine.	Rodrigo dos Reis (reisro)			         //
//---------------------------------------------------------------------------//

#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include "RainForest.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Setup Game Engine Configuration
	rfConfig engineConfig;

	// Only OS supported by now is Windows
	engineConfig.platform = EngineConfig::Platform::Windows;

	// Only Graphics API is DirectX 9
	engineConfig.graphicsAPI = EngineConfig::GraphicsAPI::DirectX9;

	// Setup engine configuration  
	rfApplication::Setup(engineConfig);

	// Start rendering the application if engine initiated properly
	if (rfApplication::Init()) rfApplication::RenderFrame();

	// Engine cleanup resources
	rfApplication::ShutDown();

	_CrtDumpMemoryLeaks();

	return 0;
}