
//---------------------------------------------------------------------------//
//                                                                           //
// File : rfWindow.h                                                         //
//                                                                           //
// Desc : Provides functionality of window creation.                         //
//                                                                           //
//---------------------------------------------------------------------------//
//     Rain Forest Game Engine.	Rodrigo dos Reis (reisro)			         //
//---------------------------------------------------------------------------//

#pragma once

#ifndef _RFAPPLICATION_WINDOW_H_
#define _RFAPPLICATION_WINDOW_H_

#include "RFGEAPI.h"
#include "System/Platform/Windows/rfWindowWin32.h"

class RFGE_API rfApplicationWindow
{
public:
	rfApplicationWindow();
	
	static rfWindow* Create();
	static bool WindowInitialized();
};

#endif _RFAPPLICATION_WINDOW_H_