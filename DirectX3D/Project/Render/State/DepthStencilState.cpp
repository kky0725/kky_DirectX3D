#include "Framework.h"
#include "DepthStencilState.h"

DepthStencilState::DepthStencilState()
{
	
	_desc.DepthEnable		= true;
	_desc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ALL;
	_desc.DepthFunc			= D3D11_COMPARISON_LESS;

	_desc.StencilEnable		= true;
	_desc.StencilReadMask	= 0xFF;
	_desc.StencilWriteMask	= 0xFF;

	_desc.FrontFace.StencilFailOp		= D3D11_STENCIL_OP_KEEP;
	_desc.FrontFace.StencilDepthFailOp	= D3D11_STENCIL_OP_INCR;
	_desc.FrontFace.StencilPassOp		= D3D11_STENCIL_OP_KEEP;
	_desc.FrontFace.StencilFunc			= D3D11_COMPARISON_ALWAYS;

	_desc.BackFace.StencilFailOp	  = D3D11_STENCIL_OP_KEEP;
	_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	_desc.BackFace.StencilPassOp	  = D3D11_STENCIL_OP_KEEP;
	_desc.BackFace.StencilFunc		  = D3D11_COMPARISON_ALWAYS;

	ChangeState();
}
DepthStencilState::~DepthStencilState()
{
	_state->Release();
}

void DepthStencilState::SetState(UINT stencilRef)
{
	DC->OMSetDepthStencilState(_state, stencilRef);
}

void DepthStencilState::ChangeState()
{
	if (_state)
		_state->Release();

	DEVICE->CreateDepthStencilState(&_desc, &_state);
}

void DepthStencilState::DepthEnable(bool value)
{
	_desc.DepthEnable = value;

	ChangeState();
}

void DepthStencilState::DepthWriteMask(D3D11_DEPTH_WRITE_MASK value)
{
	_desc.DepthWriteMask = value;

	ChangeState();
}


