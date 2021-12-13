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

#pragma once

#ifndef _RFWINDOWSYSTEMWIN32_H_
#define _RFWINDOWSYSTEMWIN32_H_

#include "System/Platform/rfWindowSystem.h"
#include "System/Platform/Windows/rfWindowWin32.h"

class RFGE_API rfWindowSystemWin32 : public rfWindowSystem
{
public:
	rfWindowSystemWin32();
	virtual ~rfWindowSystemWin32();

	HWND		Window() override;
	HINSTANCE	WindowInstance() override;
	bool		Initialized() override;

	bool Initialize() override;

private:
	HINSTANCE		hInstance;
	HWND			hWnd;
	rfWindowWin32*  windowWin32;
};

#endif _RFWINDOWSYSTEMWIN32_H_