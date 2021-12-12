#include "Input/rfInput.h"

rfInput* Input;

rfInput::rfInput()
{
}

rfInput::~rfInput()
{
}

void rfInput::InitializeDirectInput(HINSTANCE appInstance, HWND hwnd, DWORD keyboardCoopFlags, DWORD mouseCoopFlags)
{
	// Zero memory.
	ZeroMemory(KeyboardState, sizeof(KeyboardState));
	ZeroMemory(&MouseState, sizeof(MouseState));

	// Init DirectInput.
	DirectInput8Create(appInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&EngineInput, 0);

	// Init keyboard.
	EngineInput->CreateDevice(GUID_SysKeyboard, &Keyboard, 0);
	Keyboard->SetDataFormat(&c_dfDIKeyboard);
	Keyboard->SetCooperativeLevel(hwnd, keyboardCoopFlags);
	Keyboard->Acquire();

	// Init mouse.
	EngineInput->CreateDevice(GUID_SysMouse, &Mouse, 0);
	Mouse->SetDataFormat(&c_dfDIMouse2);
	Mouse->SetCooperativeLevel(hwnd, mouseCoopFlags);
	Mouse->Acquire();
}

void rfInput::Poll()
{
	// Poll mouse
	HRESULT hr = Mouse->GetDeviceState(sizeof(DIMOUSESTATE2),
		(void**)&MouseState);

	if (FAILED(hr))
	{
		// Mouse lost, zero out mouse data structure.
		ZeroMemory(&MouseState, sizeof(MouseState));

		// Try to acquire for next time we poll.
		hr = Mouse->Acquire();
	}
}

bool rfInput::KeyDown(unsigned char key)
{
	return (KeyboardState[key] & 0x80) != 0;
}

bool rfInput::MouseButtonDown(int button)
{
	return (MouseState.rgbButtons[button] & 0x80) != 0;
}
