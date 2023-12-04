#pragma once
#include "Device.h"
#include "Input.h"
#include "Writer.h"
#include "Timer.h"
#include "FPSCalculator.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"

class GameCore : public Device
{
public:
	Writer	_writer;
	Timer	_gameTimer;
	bool	_isGameRun = true;
public:
	IDXGISurface1*		_backBuffer;
	
public:
	virtual bool	Init()		{ return true; }; 
	virtual bool	Frame()		{ return true; }; 
	virtual bool	Render()	{ return true; }; 
	virtual bool	Release()	{ return true; };
private:
	bool	CoreInit(); 
	bool	CoreFrame();
	bool	CorePreRender();
	bool	CoreRender();
	bool	CorePostRender();
	bool	CoreRelease();
public:
	bool	Run() override;
};

