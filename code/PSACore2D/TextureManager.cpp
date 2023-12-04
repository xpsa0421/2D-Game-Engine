#include "TextureManager.h"

void TextureManager::SetDevice(ID3D11Device* device, ID3D11DeviceContext* context)
{
	_device = device;
	_immediateContext = context;
}

Texture* TextureManager::LoadTexture(std::wstring fileName)
{
	HRESULT result;
	Texture* texture = FindTexture(fileName);

	if (texture != nullptr)
	{
		return texture;
	}
	else
	{
		texture = new Texture;
		result = texture->Create(_device, _immediateContext, fileName);
		if (SUCCEEDED(result))
		{
			_textures.insert(std::make_pair(fileName, texture));
		}
		return texture;
	}
}

Texture* TextureManager::FindTexture(std::wstring fileName)
{
	auto texture = _textures.find(fileName);
	if (texture != _textures.end())
		return texture->second;
	else 
		return nullptr;
}

bool TextureManager::Release()
{
	for (auto texture : _textures)
	{
		Texture* t = texture.second;
		if (t) t->Release();
		delete t;
	}
	_textures.clear();
	return true;
}

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	Release(); 
}