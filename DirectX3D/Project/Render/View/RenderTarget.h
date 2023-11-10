#pragma once
class RenderTarget
{
public:
	RenderTarget(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	~RenderTarget();

	void Set(DepthStencil* depthStencil, Vector4 clearColor = Vector4(1, 1, 1, 1));

	ID3D11RenderTargetView*		GetRTV() { return _rtv; }
	ID3D11ShaderResourceView*	GetSRV() { return _srv; }

	static void SetMulti(RenderTarget** targets, UINT count, DepthStencil* depthStencil, Vector4 clearColor = {1, 1, 1, 1});

private:
	void CreateRTVTexture();
	void CreateRTV();
	void CreateSRV();

private:
	UINT _width, _height;

	bool _isStencil = false;

	ID3D11Texture2D*			_rtvTexture;
	ID3D11RenderTargetView*		_rtv;
	ID3D11ShaderResourceView*	_srv;
};