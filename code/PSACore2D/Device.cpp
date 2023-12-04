#include "Device.h"

bool		Device::Init()
{ 
    HRESULT hr;
    if (FAILED(hr = CreateDXGIDevice()))
    {
        return false;
    }
    if (FAILED(hr = CreateDevice()))
    {
        return false;
    }
    if (FAILED(hr = CreateSwapChain()))
    {
        return false;
    }
    if (FAILED(hr = CreateRenderTargetView()))
    {
        return false;
    }
    CreateViewport();
    return true;
}

bool		Device::Frame()
{
    return true;
}

bool		Device::Render()
{  
    return true;
}

bool		Device::Release()
{
    _device             = nullptr;
    _immediateContext   = nullptr;
    _factory            = nullptr;
    _swapChain          = nullptr;
    _rtv                = nullptr;
    return true;
}  

HRESULT Device::CreateDevice()
{
    HRESULT hr;
    UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevel;
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
    };
    UINT featureLevelCount = 1;
    hr = D3D11CreateDevice( nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, 
                            createDeviceFlags, featureLevels, featureLevelCount, D3D11_SDK_VERSION,
                            &_device, &featureLevel, &_immediateContext );
    return hr;
}

HRESULT Device::CreateDXGIDevice()
{
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&_factory);
    return hr;
}

HRESULT Device::CreateSwapChain( )
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));

    sd.BufferCount                         = 1;
    sd.BufferDesc.Width                    = g_rectClient.right;
    sd.BufferDesc.Height                   = g_rectClient.bottom;
    sd.BufferDesc.Format                   = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage                         = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow                        = g_wnd;
    sd.Windowed                            = true;
    sd.BufferDesc.RefreshRate.Numerator    = 60;
    sd.BufferDesc.RefreshRate.Denominator  = 1;
    sd.SampleDesc.Count                    = 1;
    sd.SampleDesc.Quality                  = 0;
    sd.Flags                               = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    return _factory->CreateSwapChain(_device, &sd, &_swapChain);
}

HRESULT Device::CreateRenderTargetView()
{
    HRESULT hr = 0;
    ID3D11Texture2D* backBuffer = nullptr;
    _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    if (backBuffer != nullptr)
    {
        hr = _device->CreateRenderTargetView(backBuffer, nullptr, &_rtv);
        backBuffer->Release();
    }
    return hr;
}

void Device::CreateViewport()
{
    D3D11_VIEWPORT vp;
    vp.Width    = FLOAT(g_rectClient.right);
    vp.Height   = FLOAT(g_rectClient.bottom);
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    _immediateContext->RSSetViewports(1, &vp);
}