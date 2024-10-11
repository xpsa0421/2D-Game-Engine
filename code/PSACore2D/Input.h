#pragma once
#include "Std.h"
#define S_Input Input::GetInstance()

enum KeyState
{
	KEY_FREE,
	KEY_UP,
	KEY_DOWN,
	KEY_HOLD
};

class Input : public Singleton<Input>
{
private:
	DWORD _keyStates[256];
public:
	POINT	_mousePos;
	bool	_keyPressed;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	bool	IsAnyKeyPressed();
	DWORD	GetKeyState(DWORD key);
};

