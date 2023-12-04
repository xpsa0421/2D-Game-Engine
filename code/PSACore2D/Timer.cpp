#include "Timer.h"

bool Timer::Init()
{
	_gameTimer = 0.0f;
	_elapseTimer = 10.0f;
	_prevTime = timeGetTime();
	return true;
}

bool Timer::Frame()
{
	DWORD currentTime = timeGetTime();
	DWORD elapseTime = currentTime - _prevTime;
	_elapseTimer = elapseTime / 1000.0f;
	_gameTimer += _elapseTimer;
	_prevTime = currentTime;
	return true;
}

bool Timer::Render()
{
	return true;
}

bool Timer::Release()
{
	return true;
}