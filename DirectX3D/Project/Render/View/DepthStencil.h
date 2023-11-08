#pragma once
class DepthStencil
{
public:
	DepthStencil(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT, bool isStencil = false);
	~DepthStencil();

	void Clear();
	ID3D11DepthStencilView*		GetDSV() { return _dsv; }
	ID3D11ShaderResourceView*	GetSRV() { return _srv; }

private:
	void CreateDSVTexture();
	void CreateDSV();
	void CreateSRV();

private:
	UINT _width, _height;

	bool _isStencil = false;

	ID3D11Texture2D*			_dsvTexture;
	ID3D11DepthStencilView*		_dsv;
	ID3D11ShaderResourceView*	_srv;
};