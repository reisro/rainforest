
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

extern "C" { _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }

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

	// Set which physics version to use
	engineConfig.physicsAPI = EngineConfig::PhysicsAPI::PhysX_ver2_81;

	// Set window resolution of the application
	engineConfig.windowResolution = EngineConfig::WindowResolution::FullHighDefinition;

	// Setup engine configuration  
	rfApplication::Setup(engineConfig);

	// Setup the game class
	rfGame volleyballGame;

	// Populate the game info with game information data
	rfGame::gameInfo volleyballGameInfo;
	volleyballGameInfo.Name = "Volleyball Court";

	// Setup the game entry function call
	volleyballGame.Setup();

	// Start rendering the application if engine initiated properly
	if (rfApplication::Init()) rfApplication::Run();

	// Engine cleanup resources
	rfApplication::ShutDown();

	_CrtDumpMemoryLeaks();

	return 0;
}