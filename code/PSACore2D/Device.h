#pragma once
#include "Window.h"

class Device : public Window
{
public:
	ID3D11Device*			_device				= nullptr;	
	ID3D11DeviceContext*	_immediateContext	= nullptr;
	IDXGIFactory*			_factory			= nullptr;
	IDXGISwapChain*			_swapChain			= nullptr;
	ID3D11RenderTargetView* _rtv				= nullptr;
public:
	HRESULT		CreateDevice();
	HRESULT		CreateDXGIDevice();
	HRESULT		CreateSwapChain();
	HRESULT		CreateRenderTargetView();
	void		CreateViewport();
public:
	virtual bool		Init(); 
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
};

