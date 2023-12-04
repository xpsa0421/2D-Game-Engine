#pragma once
#include "Std.h"

class DxState
{
public:
	static ID3D11SamplerState*	g_SSSmooth;
	static ID3D11SamplerState*	g_defaultSS;
	static ID3D11BlendState*	g_defaultBS;
public:
	static bool SetState(ID3D11Device* device);
	static bool Release();
};

