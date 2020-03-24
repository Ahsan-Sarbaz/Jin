#include "DX11.h"

ID3D11Device* DX11::device = nullptr;
ID3D11DeviceContext* DX11::context = nullptr;
IDXGISwapChain* DX11::swapChain = nullptr;
ID3D11RenderTargetView* DX11::renderTargetView = nullptr;
DX11Config DX11::config = {};

void DX11::Init(const DX11Config& _config)
{
	config = _config;

	DXGI_SWAP_CHAIN_DESC scd = {};
	scd.BufferDesc.Width = config.width;
	scd.BufferDesc.Height = config.height;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = config.windowHanlde;
	scd.Windowed = true;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferCount = 2;

	UINT createDeviceFlags = 0;
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &scd, &swapChain, &device, &featureLevel, &context) != S_OK)
		return;

	ID3D11Texture2D* pBackBuffer;
	swapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	device->CreateRenderTargetView(pBackBuffer, NULL, &renderTargetView);
	pBackBuffer->Release();

}

void DX11::Shutdown()
{
	if (renderTargetView) { renderTargetView->Release(); renderTargetView = NULL; }
	if (swapChain) { swapChain->Release(); swapChain = NULL; }
	if (context) { context->Release(); context = NULL; }
	if (device) { device->Release(); device = NULL; }
}
