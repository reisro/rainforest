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

#ifndef _RFWINDOWSYSTEM_H_
#define _RFWINDOWSYSTEM_H_

#pragma once

#include "RFGEAPI.h"
#include "System/Platform/rfWindow.h"
#include <Windows.h>

class RFGE_API rfWindowSystem
{
public:
	rfWindowSystem() {};
	virtual ~rfWindowSystem() {};

	virtual HWND			Window();

	static void				CreateInstance();
	static void				CreateRFWindow();
	static rfWindowSystem*	GetInstance();

	static bool				initialized;

protected:
	rfWindow* window;
	static rfWindowSystem* Singleton;
};

#endif _RFWINDOWSYSTEM_H_



