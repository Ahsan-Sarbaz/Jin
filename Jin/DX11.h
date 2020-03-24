#pragma once
#include "Defines.h"
#include "Types.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")


struct DX11Config
{
	u32 width;
	u32 height;
	HWND windowHanlde;
};

class DX11
{
private:
	static ID3D11Device* device;
	static ID3D11DeviceContext* context;
	static IDXGISwapChain* swapChain;
	static ID3D11RenderTargetView* renderTargetView;
	static DX11Config config;

public:
	static void Init(const DX11Config& config);
	static void Shutdown();


	JIN_INLINE static ID3D11Device* GetDevice() { return device; }
	JIN_INLINE static ID3D11DeviceContext* GetContext() { return context; }
	JIN_INLINE static IDXGISwapChain* GetSwaChain() { return swapChain; }
	JIN_INLINE static ID3D11RenderTargetView* GetRenderTarget() { return renderTargetView; }
};

