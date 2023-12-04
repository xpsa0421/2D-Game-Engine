#pragma once
#include "Texture.h"
#define S_TexManager TextureManager::GetInstance()

class TextureManager : public Singleton<TextureManager>
{
private:
	friend class Singleton<TextureManager>;
	std::map<std::wstring, Texture*> _textures;
public:
	ID3D11Device*			_device				= nullptr;
	ID3D11DeviceContext*	_immediateContext	= nullptr;
public:
	void		SetDevice(ID3D11Device* device, ID3D11DeviceContext* context);
	Texture*	LoadTexture(std::wstring fileName);
	Texture*	FindTexture(std::wstring fileName);
	bool		Release();
private:
	TextureManager();
public:
	~TextureManager();
};

