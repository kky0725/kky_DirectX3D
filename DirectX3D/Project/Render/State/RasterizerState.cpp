#include "Framework.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState()
{
	_desc.CullMode = D3D11_CULL_BACK;
	//_desc.FillMode = D3D11_FILL_WIREFRAME;
	_desc.FillMode = D3D11_FILL_SOLID;

	DEVICE->CreateRasterizerState(&_desc, &_rasterizerStae);
}

RasterizerState::~RasterizerState()
{
	_rasterizerStae->Release();
}

void RasterizerState::SetState()
{
	DC->RSSetState(_rasterizerStae);
}
