#pragma once
class DepthStencilState
{
public:
	DepthStencilState();
	~DepthStencilState();

	void SetState(UINT stencilRef = 1);
	void ChangeState();
	void DepthEnable(bool value);

	void DepthWriteMask(D3D11_DEPTH_WRITE_MASK value);

private:
	ID3D11DepthStencilState* _state;

	D3D11_DEPTH_STENCIL_DESC _desc = {};
};