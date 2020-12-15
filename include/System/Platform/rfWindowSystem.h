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

	static bool				Initialized();
	static void				CreateInstance();
	static void				CreateSpecificWindow();
	static rfWindowSystem*	GetInstance();
};

#endif _RFWINDOWSYSTEM_H_