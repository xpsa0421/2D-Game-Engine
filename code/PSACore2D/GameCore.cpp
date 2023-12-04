#include "GameCore.h"

bool		GameCore::CoreInit()
{
	Device::Init();
	DxState::SetState(_device);
	_gameTimer.Init();
	S_SoundManager.Init();
	S_TexManager.SetDevice(_device, _immediateContext);
	S_ShaderManager.SetDevice(_device, _immediateContext);
	S_FPSCalc.Init();
	S_Input.Init();

	_writer.Init();
	_swapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&_backBuffer);
	_writer.Set(_backBuffer);

    return Init();
}

bool		GameCore::CoreFrame()
{
	S_SoundManager.Frame();
	S_Input.Frame();
	_gameTimer.Frame();
	S_FPSCalc.Frame();
	_writer.Frame();
    return Frame();
}

bool		GameCore::CorePreRender()
{
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };
	_immediateContext->OMSetRenderTargets(1, &_rtv, NULL);
	_immediateContext->ClearRenderTargetView(_rtv, color);
	_immediateContext->PSSetSamplers(0, 1, &DxState::g_defaultSS);
	_immediateContext->OMSetBlendState(DxState::g_defaultBS, 0, -1);
    return true;
}

bool		GameCore::CoreRender()
{  	
	CorePreRender();
	Render();
	S_Input.Render();
	S_FPSCalc.Render();
	_gameTimer.Render();
	/*_writer._textContent = std::to_wstring(playerPos.x) + L"\n"
		+ std::to_wstring(playerPos.y);
	_writer.Render();*/
	CorePostRender();
    return true;
}

bool		GameCore::CorePostRender()
{
	_swapChain->Present(0, 0);
    return true;
}

bool		GameCore::CoreRelease()
{   
	_backBuffer->Release();
	Release();
	S_Input.Release();
	S_FPSCalc.Release();
	_gameTimer.Release();
	_writer.Release();
	DxState::Release();
	Device::Release();
    return true;
}

bool        GameCore::Run()
{    
	CoreInit();	
	while (_isGameRun)
	{
		if (Window::Run() == false)
		{
			_isGameRun = false;
		}
		else
		{
			if (!CoreFrame() || !CoreRender())
			{
				_isGameRun = false;
			}
			
		}
	}
	CoreRelease();
	return true;
}