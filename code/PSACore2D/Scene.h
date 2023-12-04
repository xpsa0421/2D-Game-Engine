#pragma once
#include "Std.h"
#include "SoundManager.h"

class Scene
{
public:
	ID3D11Device*			_device				= nullptr;
	ID3D11DeviceContext*	_immediateContext	= nullptr;
public:
	Sound*		_BGMusic	= nullptr;
	bool		_isNextScene = false;
public:
	virtual bool SetDevice(
		ID3D11Device* device, ID3D11DeviceContext* immediateContext);
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	virtual bool IsNextScene() { return _isNextScene; }
	virtual bool IsGameQuit() { return false; }
	virtual void RestartScene() {};
};
