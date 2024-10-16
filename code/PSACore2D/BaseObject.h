#pragma once
#include "TextureManager.h"
#include "ShaderManager.h"
#include "Collision2D.h"
#include "Camera.h"

struct Vertex
{
	Vector3 p;
	Vector4 c;
	Vector2 t;
};

class BaseObject
{
public:
	ID3D11Device*			_device				= nullptr;
	ID3D11DeviceContext*	_immediateContext	= nullptr;
	ID3D11Buffer*			_indexBuffer;
	ID3D11Buffer*			_vertexBuffer;
	ID3D11InputLayout*		_vertexLayout;
	Texture*				_texture; 
	Shader*					_shader;
	Rect					_collider;
	std::vector<Vertex>		_vertices;
	std::vector<DWORD>		_indices;
public:
	bool					_rectSet			= false;
	Camera*					_renderCam			= nullptr;
	Texture*				_maskTexture		= nullptr;
	POINT					_imageSize;
	Rect					_rectInit;
	Rect					_rectUV;
	Vector2					_pos;
	Vector2					_drawPos;
	Vector2					_drawSize;
public:
	virtual void		CreateVertexData();
	virtual void		CreateIndexData();
	virtual HRESULT		CreateVertexBuffer();
	HRESULT				CreateIndexBuffer();
	HRESULT				CreateVertexLayout();
public:
	void				SetMask(Texture* maskTex);
	bool				LoadShader(W_STR shaderFileName);
	bool				LoadTexture(W_STR texFileName);
public:
	virtual bool		Create( ID3D11Device* device, ID3D11DeviceContext* immediateContext,
						W_STR texFileName, W_STR shaderFileName	);
public:
	virtual void		SetCamera(Camera* cam);
	virtual void		SetColour(Vector4 color);
	virtual void		SetRect(Rect rect);
	virtual void		SetPosition(Vector2 pos);
	void				ScreenToCamera();
	virtual void		ScreenToNDC();
	virtual void		UpdateVertexBuffer();
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		PreRender();
	virtual bool		PostRender();
	virtual bool		Render();
	virtual bool		Release();
};
