#include "Shader.h"

bool Shader::Init()
{
	return true;
}

bool Shader::Frame()
{
	return true;
}

bool Shader::Render()
{
	return true;
}

bool Shader::Release()
{
	if (_vertexShader)	_vertexShader->Release();
	if (_pixelShader)	_pixelShader->Release();
	if (_pixelShaderNoTexture)	_pixelShaderNoTexture->Release();
	if (_VSCode)		_VSCode->Release();
	if (_PSCode)		_PSCode->Release();
	if (_PSCodeNoTexture)		_PSCode->Release();

	_pixelShaderNoTexture = nullptr;
	_pixelShader	= nullptr;
	_vertexShader	= nullptr;
	_VSCode			= nullptr;
	_PSCode			= nullptr;
	_PSCodeNoTexture = nullptr;

	return true;
}

HRESULT Shader::Create(
		ID3D11Device* device, ID3D11DeviceContext* immediateContext, W_STR shaderFileName)
{
	_device = device;
	_immediateContext = immediateContext;

	HRESULT VSResult = CreateVertexShader(shaderFileName);
	HRESULT PSResult = CreatePixelShader(shaderFileName);

	if (SUCCEEDED(VSResult) && SUCCEEDED(PSResult))
		return S_OK;
	else
		return E_FAIL;
}

HRESULT	Shader::CreateVertexShader(W_STR fileName)
{
	HRESULT result;
	ID3DBlob* errorCode = nullptr;

	result = D3DCompileFromFile(
		fileName.c_str(),
		NULL,
		NULL,
		"VSMain",
		"vs_5_0",
		0,
		0,
		&_VSCode,
		&errorCode
	);
	if (FAILED(result))
	{
		if (errorCode)
		{
			OutputDebugStringA((char*)errorCode->GetBufferPointer());
			errorCode->Release();
		}
		return E_FAIL;
	}

	result = _device->CreateVertexShader(
		_VSCode->GetBufferPointer(),
		_VSCode->GetBufferSize(),
		NULL,
		&_vertexShader
	);

	return result;
}

HRESULT	Shader::CreatePixelShader(W_STR fileName)
{
	HRESULT result;
	ID3DBlob* errorCode = nullptr;

	// Texture shader
	result = D3DCompileFromFile(
		fileName.c_str(),
		NULL,
		NULL,
		"PSMain",
		"ps_5_0",
		0,
		0,
		&_PSCode,
		&errorCode
	);
	if (FAILED(result))
	{
		if (errorCode)
		{
			OutputDebugStringA((char*)errorCode->GetBufferPointer());
			errorCode->Release();
		}
		return E_FAIL;
	}

	result = _device->CreatePixelShader(
		_PSCode->GetBufferPointer(),
		_PSCode->GetBufferSize(),
		NULL,
		&_pixelShader
	);
	if (FAILED(result)) return E_FAIL;

	// Non-texture shader
	result = D3DCompileFromFile(
		fileName.c_str(),
		NULL,
		NULL,
		"PSMainNoTexture",
		"ps_5_0",
		0,
		0,
		&_PSCodeNoTexture,
		&errorCode
	);
	if (FAILED(result))
	{
		if (errorCode)
		{
			OutputDebugStringA((char*)errorCode->GetBufferPointer());
			errorCode->Release();
		}
		return E_FAIL;
	}

	result = _device->CreatePixelShader(
		_PSCodeNoTexture->GetBufferPointer(),
		_PSCodeNoTexture->GetBufferSize(),
		NULL,
		&_pixelShaderNoTexture
	);
	if (FAILED(result)) return E_FAIL;

	return result;
}