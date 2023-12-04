#pragma once
#include "Std.h"
#include "dxtk/WICTextureLoader.h"
#include "dxtk/DDSTextureLoader.h"
#pragma comment(lib, "DirectXTK.lib")

class Texture
{
protected:
	ID3D11Device*			_device				= nullptr;
	ID3D11DeviceContext*	_immediateContext	= nullptr;
public:
	ID3D11Texture2D*			_texture		= nullptr;
	ID3D11ShaderResourceView*	_textureSRV		= nullptr;
	D3D11_TEXTURE2D_DESC		_desc;
public:
	HRESULT	Create(ID3D11Device* device, ID3D11DeviceContext* immediateContext, std::wstring fileName);
	void	Apply(ID3D11DeviceContext* immediateContext, UINT slot = 0);
	bool	Release();
};

