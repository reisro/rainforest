
//---------------------------------------------------------------------------//
//                                                                           //
// File : rfWindowWin32.h                                                         //
//                                                                           //
// Desc : Provides win32 apps functionality of window creation.              //
//                                                                           //
//---------------------------------------------------------------------------//
//     Rain Forest Game Engine.	Rodrigo dos Reis (reisro)			         //
//---------------------------------------------------------------------------//

#pragma once

#ifndef _RFWINDOW_WIN32_H_
#define _RFWINDOW_WIN32_H_

#include "System/Platform/rfWindow.h"

class RFGE_API rfWindowWin32: public rfWindow
{
	friend class rfWindowSystemWin32;

public:
	rfWindowWin32();
	virtual ~rfWindowWin32();

	void      Create() override;
	void      Close() override;
	HWND	  GetWindow() override;
	HINSTANCE GetWindowInstance() override;

	void CreateWin32Window();

protected:
	HINSTANCE	hInstance;
	LPCSTR		Name;
	HWND		hWnd;
	WNDCLASS	wc;
	LPCSTR		titleName;

	int cmdShow;

	// windows callback event handler 
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif _RFWINDOW_WIN32_H_
