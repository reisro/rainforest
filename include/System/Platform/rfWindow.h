
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

#ifndef _RFWINDOW_H_
#define _RFWINDOW_H_

#include "RFGEAPI.h"
#include <Windows.h>

class RFGE_API rfWindow
{
public :

	static void		CreateInstance();
	virtual void	Create() = 0;
	virtual void	Close()  = 0;
	virtual HWND	GetWindow() = 0;

	bool initialized;

protected:
	static rfWindow* Singleton;
};

#endif _RFWINDOW_H_