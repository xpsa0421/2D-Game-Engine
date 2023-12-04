#pragma once
#include "Shader.h"
#define S_ShaderManager ShaderManager::GetInstance()

class ShaderManager : public Singleton<ShaderManager>
{
private:
	friend class Singleton<ShaderManager>;
	std::map<std::wstring, Shader*> _shaders;
public:
	ID3D11Device*			_device				= nullptr;
	ID3D11DeviceContext*	_immediateContext	= nullptr;
public:
	void		SetDevice(ID3D11Device* device, ID3D11DeviceContext* context);
	Shader*		LoadShader(W_STR shaderFileName);
	Shader*		FindShader(W_STR shaderFileName);
	bool		Release();
private:
	ShaderManager();
public:
	~ShaderManager();
};

