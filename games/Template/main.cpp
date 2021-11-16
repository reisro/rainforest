
//---------------------------------------------------------------------------//
//                                                                           //
// File : main.cpp                                                           //
//                                                                           //
// Desc : Application game entry point									         //
//                                                                           //
//                                                                           //
//---------------------------------------------------------------------------//
//     Rain Forest game engine.	Rodrigo dos Reis (reisro)			         //
//---------------------------------------------------------------------------//

#define _CRTDBG_MAP_ALLOC

#include <RainForest.h>
#include "Game/Public/VolleyballCourtGame.h"
#include <stdlib.h>
#include <crtdbg.h>

extern "C" { _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Setup Game Engine Configuration
	rfConfig engineConfig;

	// Setup engine configuration  
	rfApplication::Setup(engineConfig);

	// Create game client instance
	VolleyballCourtGame game;

	// Start rendering the application if engine initiated properly
	if (rfApplication::Init())
	{
		// Setup assets to the game world
		game.LoadAssets();

		rfApplication::Run();
	}

	// Engine cleanup resources
	rfApplication::ShutDown();

	// Checking out memory leaks if any
	_CrtDumpMemoryLeaks();

	return 0;
}