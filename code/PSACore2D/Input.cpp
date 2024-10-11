#include "Input.h"

DWORD Input::GetKeyState(DWORD key)
{
	return _keyStates[key];
}

bool Input::IsAnyKeyPressed()
{
	return _keyPressed;
}

bool Input::Init()
{
	ZeroMemory(_keyStates, sizeof(DWORD) * 256);
	return true;
}

bool Input::Frame()
{
	::GetCursorPos(&_mousePos);
	::ScreenToClient(g_wnd, &_mousePos);

	_keyPressed = false;
	for (int i = 0; i < 256; i++)
	{
		SHORT keyState = ::GetAsyncKeyState(i);

		if (keyState & 0x8000) // if pressed
		{
			_keyPressed = true;
			if (_keyStates[i] == KEY_FREE || _keyStates[i] == KEY_UP)
				_keyStates[i] = KEY_DOWN;
			else
				_keyStates[i] = KEY_HOLD;
		}
		else
		{
			if (_keyStates[i] == KEY_DOWN || _keyStates[i] == KEY_HOLD)
				_keyStates[i] = KEY_UP;
			else
				_keyStates[i] = KEY_FREE;
		}
	}

	return true;
}

bool Input::Render()
{
	return true;
}

bool Input::Release()
{
	return true;
}