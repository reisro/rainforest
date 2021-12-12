
//---------------------------------------------------------------------------//
//                                                                           //
// File : rfInput.h                                                          //
//                                                                           //
// Desc : Provides input functionality to read input from keyboard           //
//															                 //
//---------------------------------------------------------------------------//
//     Rain Forest 2021.	Rodrigo dos Reis (reisro)			             //
//---------------------------------------------------------------------------//

#pragma once

#ifndef _RFDIRECTINPUT_H_
#define _RFDIRECTINPUT_H_

#include <dinput.h>
#include <d3dx9.h>

class rfInput
{
public:

	rfInput();
	~rfInput();
	void InitializeDirectInput(HINSTANCE appInstance, HWND hwnd,
		DWORD keyboardCoopFlags, DWORD mouseCoopFlags);
	void Poll();
	bool KeyDown(unsigned char key);
	bool MouseButtonDown(int button);

	IDirectInput8*       EngineInput;
	IDirectInputDevice8* Keyboard;
	char                 KeyboardState[256];
	IDirectInputDevice8* Mouse;
	DIMOUSESTATE2        MouseState;
};

#endif _RFDIRECTINPUT_H_