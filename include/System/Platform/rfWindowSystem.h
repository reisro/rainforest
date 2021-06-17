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
#include "System/Subsystem.h"
#include "System/Interfaces/IStartup.h"

class RFGE_API rfWindowSystem: public rfSubsystem, public IStartup
{
public:

	rfWindowSystem() {};
	virtual ~rfWindowSystem() {};

	// interface
	bool 				    Initialized() override;

	virtual HWND			Window();

	static bool				Initialized();
	static void				CreateSpecificWindow();
	static rfWindowSystem*	GetInstance();
};

#endif _RFWINDOWSYSTEM_H_