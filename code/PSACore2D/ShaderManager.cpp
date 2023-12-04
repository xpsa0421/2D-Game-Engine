#include "ShaderManager.h"

void ShaderManager::SetDevice(ID3D11Device* device, ID3D11DeviceContext* context)
{
	_device = device;
	_immediateContext = context;
}

Shader* ShaderManager::LoadShader(W_STR shaderFileName)
{
	HRESULT result;
	Shader* shader = FindShader(shaderFileName);

	if (shader != nullptr)
	{
		return shader;
	}
	else
	{
		shader = new Shader;
		result = shader->Create(_device, _immediateContext, shaderFileName);
		if (SUCCEEDED(result))
		{
			_shaders.insert(std::make_pair(shaderFileName, shader));
		}
		return shader;
	}
}

Shader* ShaderManager::FindShader(W_STR shaderFileName)
{
	auto shader = _shaders.find(shaderFileName);
	if (shader != _shaders.end())
		return shader->second;
	else
		return nullptr;
}

bool ShaderManager::Release()
{
	for (auto shader : _shaders)
	{
		Shader* s = shader.second;
		if (s) s->Release();
		delete s;
		s = nullptr;
	}
	_shaders.clear();
	return true;
}

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	Release();
}