#pragma once
#include "Std.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

class Writer
{
public:
	ID2D1Factory*			_d2dFactory;
	IDWriteFactory*			_writeFactory;
	ID2D1RenderTarget*		_d2dRT;
	IDWriteTextFormat*		_textFormat;
	D2D1_COLOR_F			_textColor;
	ID2D1SolidColorBrush*	_colorBrush;
	std::wstring			_textContent;
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
public:
	bool	Set(IDXGISurface1* surface);
	bool	Draw(float x, float y, std::wstring text, D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::White, 1.0f));

};

