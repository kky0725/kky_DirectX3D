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

void RasterizerState::ChangeState(D3D11_FILL_MODE mode)
{
	if (_rasterizerStae != nullptr)
		_rasterizerStae->Release();

	_desc.FillMode = mode;

	DEVICE->CreateRasterizerState(&_desc, &_rasterizerStae);
	DC->RSSetState(_rasterizerStae);
}
