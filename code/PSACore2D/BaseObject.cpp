#include "BaseObject.h"

/*----------------------------------------------------------
|	OBJECT CREATION                                         |
 -----------------------------------------------------------*/

void BaseObject::CreateVertexData()
{
	_vertices.resize(4);

	_vertices[0].p = { -1.0f, 1.0f, 0.0f };
	_vertices[0].c = { 1.0f, 1.0f, 1.0f, 1.0f };
	_vertices[0].t = { 0.0f, 0.0f };

	_vertices[1].p = { 1.0f, 1.0f, 0.0f };
	_vertices[1].c = { 1.0f, 1.0f, 1.0f, 1.0f };
	_vertices[1].t = { 1.0f, 0.0f };

	_vertices[2].p = { -1.0f, -1.0f, 0.0f };
	_vertices[2].c = { 1.0f, 1.0f, 1.0f, 1.0f };
	_vertices[2].t = { 0.0f, 1.0f };

	_vertices[3].p = { 1.0f, -1.0f, 0.0f };
	_vertices[3].c = { 1.0f, 1.0f, 1.0f, 1.0f };
	_vertices[3].t = { 1.0f, 1.0f };
}

void BaseObject::CreateIndexData()
{
	_indices.resize(6);

	_indices[0] = 0;
	_indices[1] = 1;
	_indices[2] = 2;
	_indices[3] = 2;
	_indices[4] = 1;
	_indices[5] = 3;
}

HRESULT	BaseObject::CreateVertexBuffer()
{
	CreateVertexData();

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.ByteWidth = sizeof(Vertex) * UINT(_vertices.size());
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subRsrcData;
	ZeroMemory(&subRsrcData, sizeof(subRsrcData));
	subRsrcData.pSysMem = &_vertices.at(0);

	HRESULT result = _device->CreateBuffer(
		&bufferDesc,
		&subRsrcData,
		&_vertexBuffer
	);
	return result;
}

HRESULT	BaseObject::CreateIndexBuffer()
{
	CreateIndexData();

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.ByteWidth = sizeof(DWORD) * UINT(_indices.size());
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subRsrcData;
	ZeroMemory(&subRsrcData, sizeof(subRsrcData));
	subRsrcData.pSysMem = &_indices.at(0);

	HRESULT result = _device->CreateBuffer(
		&bufferDesc,
		&subRsrcData,
		&_indexBuffer
	);
	return result;
}

HRESULT	BaseObject::CreateVertexLayout()
{
	D3D11_INPUT_ELEMENT_DESC elementDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	HRESULT result = _device->CreateInputLayout(
		elementDesc,
		sizeof(elementDesc) / sizeof(elementDesc[0]),
		_shader->_VSCode->GetBufferPointer(),
		_shader->_VSCode->GetBufferSize(),
		&_vertexLayout
	);
	return result;
}

bool BaseObject::LoadShader(W_STR shaderFileName)
{
	_shader = S_ShaderManager.LoadShader(shaderFileName);
	if (_shader) return true;
	else return false;
}

bool BaseObject::LoadTexture(std::wstring texFileName)
{
	if (texFileName == L"") return true;
	_texture = S_TexManager.LoadTexture(texFileName);
	if (_texture)
	{
		_imageSize.x = _texture->_desc.Width;
		_imageSize.y = _texture->_desc.Height;
		return true;
	}
	else return false;
}

void BaseObject::SetMask(Texture* maskTex)
{
	_maskTexture = maskTex;
}

bool BaseObject::Create(
	ID3D11Device* device, ID3D11DeviceContext* immediateContext,
	W_STR texFileName, W_STR shaderFileName)
{
	_device = device;
	_immediateContext = immediateContext;

	if (FAILED(CreateVertexBuffer()))				return false;
	if (FAILED(CreateIndexBuffer()))				return false;
	if (!LoadShader(shaderFileName))				return false;
	if (FAILED(CreateVertexLayout()))				return false;
	if (!LoadTexture(texFileName))					return false;

	return true;
}

/*----------------------------------------------------------
|	OBJECT POSITIONING AND SIZING                           |
 -----------------------------------------------------------*/

void BaseObject::SetCameraPos(Vector2 cameraPos)
{
	_cameraSet = true;
	_cameraPos = cameraPos;
}

void BaseObject::SetCameraSize(Vector2 cameraSize)
{
	_cameraSize = cameraSize;
}

void BaseObject::ScreenToCamera(Vector2 cameraPos, Vector2 cameraSize)
{
	_drawPos.x = (_collider.x1 - cameraPos.x) * (2.0f / cameraSize.x);
	_drawPos.y = (_collider.y1 - cameraPos.y) * (2.0f / cameraSize.y) * -1.0f;
	_drawSize.x = (_rectInit.w / cameraSize.x) * 2;
	_drawSize.y = (_rectInit.h / cameraSize.y) * 2;
}

void BaseObject::ScreenToNDC()
{
	_drawPos.x = (_collider.x1 / g_rectClient.right) * 2.0f - 1.0f;
	_drawPos.y = -((_collider.y1 / g_rectClient.bottom) * 2.0f - 1.0f);
	_drawSize.x = (_rectInit.w / g_rectClient.right) * 2;
	_drawSize.y = (_rectInit.h / g_rectClient.bottom) * 2;
}

void BaseObject::SetPosition(Vector2 pos)
{
	_pos = pos;
	_collider.Set(
		pos.x,
		pos.y,
		_rectInit.w,
		_rectInit.h
	);
	ScreenToNDC();
	UpdateVertexBuffer();
}

void BaseObject::SetPosition(Vector2 pos, Vector2 cameraPos)
{
	_pos = pos;
	_cameraPos = cameraPos;
	_collider.Set(
		pos.x,
		pos.y,
		_rectInit.w,
		_rectInit.h
	);
	ScreenToCamera(cameraPos, _cameraSize);
	UpdateVertexBuffer();
}

void BaseObject::SetRect(Rect rect)
{
	_rectSet = true;
	_rectInit = rect;
	if (_texture == nullptr) return;

	_rectUV.x1 = rect.x1 / _imageSize.x;
	_rectUV.y1 = rect.y1 / _imageSize.y;
	_rectUV.w = rect.w / _imageSize.x;
	_rectUV.h = rect.h / _imageSize.y;
}

void BaseObject::SetColour(Vector4 colour)
{
	_vertices[0].c = colour;
	_vertices[1].c = colour;
	_vertices[2].c = colour;
	_vertices[3].c = colour;
}

void BaseObject::UpdateVertexBuffer()
{
	if (!_rectSet) return;

	_vertices[0].p = { _drawPos.x, _drawPos.y, 0.0f };
	_vertices[0].t = { _rectUV.x1, _rectUV.y1 };

	_vertices[1].p = { _drawPos.x + _drawSize.x, _drawPos.y, 0.0f };
	_vertices[1].t = { _rectUV.x1 + _rectUV.w, _rectUV.y1 };

	_vertices[2].p = { _drawPos.x, _drawPos.y - _drawSize.y, 0.0f };
	_vertices[2].t = { _rectUV.x1, _rectUV.y1 + _rectUV.h };

	_vertices[3].p = { _drawPos.x + _drawSize.x, _drawPos.y - _drawSize.y, 0.0f };
	_vertices[3].t = { _rectUV.x1 + _rectUV.w, _rectUV.y1 + _rectUV.h };

	_immediateContext->UpdateSubresource(
		_vertexBuffer, NULL, nullptr, &_vertices.at(0), 0, 0);
}


/*----------------------------------------------------------
|	OBJECT RENDERING		                                |
 -----------------------------------------------------------*/

bool BaseObject::Init()
{
	return true;
}

bool BaseObject::Frame()
{
	if (_cameraSet)	SetPosition(_pos, _cameraPos);
	else
	{
		_immediateContext->UpdateSubresource(
			_vertexBuffer, 0, nullptr,
			&_vertices.at(0), 0, 0
		);
	}
	return true;
}

bool BaseObject::PreRender()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	
	_immediateContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
	_immediateContext->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, offset);
	_immediateContext->IASetInputLayout(_vertexLayout);
	_immediateContext->VSSetShader(_shader->_vertexShader, NULL, 0);
	_immediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (_texture != nullptr) 
	{
		_immediateContext->PSSetShader(_shader->_pixelShader, NULL, 0);
		_immediateContext->PSSetShaderResources(0, 1, &(_texture->_textureSRV));
	}
	else // no-texture object
	{
		_immediateContext->PSSetShader(_shader->_pixelShaderNoTexture, NULL, 0);
	}
	
	return true;
}

bool BaseObject::PostRender()
{
	if (_indexBuffer == nullptr)
		_immediateContext->Draw(UINT(_vertices.size()), 0);
	else
		_immediateContext->DrawIndexed(UINT(_indices.size()), 0, 0);

	return true;
}

bool BaseObject::Render()
{
	PreRender();
	PostRender();
	return true;
}

bool BaseObject::Release()
{
	if (_texture)		_texture->Release();
	if (_vertexBuffer)	_vertexBuffer->Release();
	if (_indexBuffer)	_indexBuffer->Release();
	if (_vertexLayout)	_vertexLayout->Release();
	if (_shader)		_shader->Release();

	_texture = nullptr;
	_vertexBuffer = nullptr;
	_indexBuffer = nullptr;
	_vertexLayout = nullptr;
	_shader = nullptr;

	return true;
}