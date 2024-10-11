#pragma once
#include "Std.h"
#pragma comment(lib, "winmm.lib")
#define S_FPSCalc FPSCalculator::GetInstance()

class FPSCalculator : public Singleton<FPSCalculator>
{
private:
	float	_elapseTimer;
	DWORD	_prevTime;
	float	_FPSTimer;
	UINT	_FPSCounter;
public:
	UINT	_FPS;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
};
