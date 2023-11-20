#include "Framework.h"
#include "BlendState.h"

BlendState::BlendState()
{
	_desc.AlphaToCoverageEnable = false;
	_desc.IndependentBlendEnable = false;

	_desc.RenderTarget[0].BlendEnable			= false;
	_desc.RenderTarget[0].SrcBlend				= D3D11_BLEND_SRC_ALPHA;//원본 색깔
	_desc.RenderTarget[0].DestBlend				= D3D11_BLEND_INV_SRC_ALPHA;//배경색
	_desc.RenderTarget[0].BlendOp				= D3D11_BLEND_OP_ADD;
	_desc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
	_desc.RenderTarget[0].DestBlendAlpha		= D3D11_BLEND_INV_SRC_ALPHA;
	_desc.RenderTarget[0].BlendOpAlpha			= D3D11_BLEND_OP_ADD;
	_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	ChangeState();
}

BlendState::~BlendState()
{
	_state->Release();
}

void BlendState::SetState()
{
	float blendFactor[] = { 0, 0, 0, 0 };
	DC->OMSetBlendState(_state, blendFactor, 0XFFFFFFFF);
}

void BlendState::ChangeState()
{
	if (_state)
		_state->Release();

	DEVICE->CreateBlendState(&_desc, &_state);
}

void BlendState::Alpha(bool value)
{
	_desc.RenderTarget[0].BlendEnable = value;

	ChangeState();
}

void BlendState::AlphaToCoverage(bool value)
{
	_desc.AlphaToCoverageEnable = value;

	ChangeState();
}

void BlendState::Additive()
{
	_desc.RenderTarget[0].BlendEnable = true;
	_desc.RenderTarget[0].DestBlend	  = D3D11_BLEND_ONE;//배경색을 비율로 섞지 않고 그대로 더해서 적용->원래보다 밝아짐

	ChangeState();
}


