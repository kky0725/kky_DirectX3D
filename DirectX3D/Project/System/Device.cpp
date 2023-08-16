#include "Framework.h"
#include "Device.h"

Device::Device()
{
	CreateDeviceAndSwapChain();
	CreateBackBuffer();
}

Device::~Device()
{
	_device->			Release();
	_deviceContext->	Release();
	_swapChain->		Release();
	_renderTargetView->	Release();
}

void Device::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = WIN_WIDTH;
	swapChainDesc.BufferDesc.Height = WIN_HEIGHT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//RGBA 8비트 * 4개 = 32비트, UNORM = Unsigned Normal = 0~1

	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	swapChainDesc.OutputWindow = hWnd;

	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	swapChainDesc.Windowed = true;

	D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&_swapChain,
		&_device,
		nullptr,
		&_deviceContext
	);
}

void Device::CreateBackBuffer()
{
	ID3D11Texture2D* backBuffer;

	_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	_device->CreateRenderTargetView(backBuffer, nullptr, &_renderTargetView);

	backBuffer->Release();

	_deviceContext->OMSetRenderTargets(1, &_renderTargetView, nullptr);
}

void Device::Clear()
{
	float clearColor[4] = { 0.33f, 0.33f, 0.4f, 1.0f };

	_deviceContext->ClearRenderTargetView(_renderTargetView, clearColor);
}

void Device::Present()
{
	_swapChain->Present(0, 0);
}
