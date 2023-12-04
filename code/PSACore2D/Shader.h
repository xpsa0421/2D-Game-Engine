#pragma once
#include "Std.h"

class Shader
{
public:
	ID3D11Device*			_device				= nullptr;
	ID3D11DeviceContext*	_immediateContext	= nullptr;
public:
	ID3D11VertexShader*		_vertexShader;
	ID3D11PixelShader*		_pixelShader;
	ID3D11PixelShader*		_pixelShaderNoTexture;
	ID3DBlob*				_VSCode				= nullptr;
	ID3DBlob*				_PSCode				= nullptr;
	ID3DBlob*				_PSCodeNoTexture	= nullptr;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	HRESULT Create(
		ID3D11Device* device, ID3D11DeviceContext* immediateContext, W_STR shaderFileName );
	HRESULT CreateVertexShader(std::wstring VSFileName);
	HRESULT CreatePixelShader(std::wstring PSFileName);
};

