#include "Texture.h"

HRESULT	Texture::Create(ID3D11Device* device, ID3D11DeviceContext* immediateContext, std::wstring fileName)
{
	_device = device;
	_immediateContext = immediateContext;

	/*HRESULT result = DirectX::CreateWICTextureFromFile(
		device,
		immediateContext,
		fileName.c_str(),
		(ID3D11Resource**)&_texture,
		&_textureSRV
	);

	if (FAILED(result))
	{
		HRESULT result = DirectX::CreateDDSTextureFromFile(
			device,
			immediateContext,
			fileName.c_str(),
			(ID3D11Resource**)&_texture,
			&_textureSRV
		);
	}*/
	
	HRESULT result = DirectX::CreateWICTextureFromFileEx(
		device,
		immediateContext,
		fileName.c_str(),
		0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		DirectX::DX11::WIC_LOADER_FLAGS::WIC_LOADER_IGNORE_SRGB,
		(ID3D11Resource**)&_texture, &_textureSRV
	);

	_texture->GetDesc(&_desc);
	return result;
}

void Texture::Apply(ID3D11DeviceContext* immediateContext, UINT slot)
{
	immediateContext->PSSetShaderResources(slot, 1, &_textureSRV);
}

bool Texture::Release()
{
	if (_texture)
	{
		_texture->Release();
	}
	if (_textureSRV)	_textureSRV->Release();

	_texture = nullptr;
	_textureSRV = nullptr;

	return true;
}