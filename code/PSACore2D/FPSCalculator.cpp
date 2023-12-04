#include "FPSCalculator.h"

float g_secondPerFrame = 0.0f;

bool FPSCalculator::Init()
{
    _elapseTimer = 10.0f;
    _prevTime = timeGetTime(); 
    return true;
}
bool FPSCalculator::Frame()
{
    DWORD currentTime = timeGetTime();
    DWORD elapseTime = currentTime - _prevTime;
    _elapseTimer = elapseTime / 1000.0f;
    
    _FPSCounter++;
    _FPSTimer += _elapseTimer;
    if (_FPSTimer >= 1.0f)
    {
        _FPS = _FPSCounter;
        _FPSCounter = 0;
        _FPSTimer -= 1.0f;
    }
    
    g_secondPerFrame = _elapseTimer;
    _prevTime = currentTime;
    return true;
}
bool FPSCalculator::Render()
{
    //OutputDebugString(std::to_wstring(_FPS).c_str());
    return true;
}
bool FPSCalculator::Release()
{
    return true;
}