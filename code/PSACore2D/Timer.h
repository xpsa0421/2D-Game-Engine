#pragma once
#include "Std.h"
#pragma comment(lib, "winmm.lib")

class Timer
{
public:
	float	_gameTimer;
private:
	DWORD	_prevTime;
	float	_elapseTimer;
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};


