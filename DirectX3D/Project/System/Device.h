#pragma once
class Device : public Singleton<Device>
{
	friend class Singleton;
private:
	Device();
	~Device();

	void CreateDeviceAndSwapChain();
	void CreateBackBuffer();

public:
	void Clear();
	void Present();

	ID3D11Device*			GetDevice() { return _device; }
	ID3D11DeviceContext*	GetDC()		{ return _deviceContext; }

private:
	ID3D11Device*		 _device;        //���𰡸� ���� �� ���, CPU�� �ٷ�� ��ü
	ID3D11DeviceContext* _deviceContext; //���𰡸� �׸� �� ���, GPU�� �ٷ�� ��ü

	IDXGISwapChain*			_swapChain;          //���� ���۸��� �����ϴ� ��ü
	ID3D11RenderTargetView* _renderTargetView;   //����۸� �����ϴ� ��ü
	ID3D11DepthStencilView* _depthStencilView;
};
