#include "Scene.h"

bool Scene::SetDevice(
	ID3D11Device* device, ID3D11DeviceContext* immediateContext)
{
	_device = device;
	_immediateContext = immediateContext;
	return true;
}

bool Scene::Init()
{
	return true;
}

bool Scene::Frame()
{
	return true;
}

bool Scene::Render()
{
	return true;
}

bool Scene::Release()
{
	return true;
}
