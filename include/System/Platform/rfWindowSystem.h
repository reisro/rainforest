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
#include "System/Interfaces/IStartup.h"

class RFGE_API rfWindowSystem: public IStartup
{
public:

	rfWindowSystem() {};
	virtual ~rfWindowSystem() {};

	static void				CreateInstance();
	static bool			    Init();

	// interface
	bool 				    Initialized() override;

	virtual bool			Initialize();
	virtual HWND			Window();

	static rfWindowSystem*	GetInstance();
};

#endif _RFWINDOWSYSTEM_H_