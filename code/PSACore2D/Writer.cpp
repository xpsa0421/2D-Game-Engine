#include "Writer.h"

bool Writer::Init()
{
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_d2dFactory);
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)&_writeFactory);
	_writeFactory->CreateTextFormat(
		L"°íµñ",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20,
		L"en-us",
		&_textFormat);
	_textContent = L"Some default text";
	_textColor = { 1, 1, 1, 1 };
	return true;
}

bool Writer::Frame()
{
	return true;
}

bool Writer::Render()
{
	
	Draw(0, 0, _textContent, _textColor);
	return true;
}

bool Writer::Release()
{
	if (_textFormat)	_textFormat->Release();
	if (_colorBrush)	_colorBrush->Release();
	if (_writeFactory)	_writeFactory->Release();
	if (_d2dRT)			_d2dRT->Release();
	if (_d2dFactory)	_d2dFactory->Release();

	_textFormat		= nullptr;
	_colorBrush		= nullptr;
	_writeFactory	= nullptr;
	_d2dRT			= nullptr;
	_d2dFactory		= nullptr;

	return true;
}

bool Writer::Set(IDXGISurface1* surface)
{
	D2D1_RENDER_TARGET_PROPERTIES rtProps;
	ZeroMemory(&rtProps, sizeof(rtProps));
	rtProps.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	rtProps.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
	rtProps.dpiX = 96;
	rtProps.dpiY = 96;
	rtProps.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	rtProps.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	_d2dFactory->CreateDxgiSurfaceRenderTarget(surface, &rtProps, &_d2dRT);
	_d2dRT->CreateSolidColorBrush(_textColor, &_colorBrush);
	return true;
}

bool Writer::Draw(float x, float y, std::wstring text, D2D1_COLOR_F color)
{
	_d2dRT->BeginDraw();

	D2D1_RECT_F rect = { x, y, FLOAT(g_rectClient.right), FLOAT(g_rectClient.bottom) };
	_colorBrush->SetColor(color);
	_colorBrush->SetOpacity(1.0f);
	
	_d2dRT->DrawText(text.c_str(), UINT(text.size()), _textFormat, rect, _colorBrush);

	_d2dRT->EndDraw();
	return true;
}