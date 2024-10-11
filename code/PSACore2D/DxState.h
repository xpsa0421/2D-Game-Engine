#pragma once
#include "Std.h"

class DxState
{
public:
	static ID3D11SamplerState*	g_SSSmooth;
	static ID3D11SamplerState*	g_SSDefault;
	static ID3D11BlendState*	g_BSDefault;
public:
	static bool SetState(ID3D11Device* device);
	static bool Release();
};
