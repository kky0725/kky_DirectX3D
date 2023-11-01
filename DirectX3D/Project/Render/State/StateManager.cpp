#include "Framework.h"
#include "StateManager.h"

StateManager::StateManager()
{
	CreateSamplerState();
	CreateRasterizerState();
	CreateBlendState();
	CreateDepthStencilState();
}

StateManager::~StateManager()
{
	delete _samplerStae;
	delete _rasterizerState;

	for (BlendState* blend : _blendStates)
		delete blend;

	for (DepthStencilState* depth : _depthStencilStates)
		delete depth;
}

void StateManager::CreateSamplerState()
{
	_samplerStae = new SamplerState();
}

void StateManager::CreateRasterizerState()
{
	_rasterizerState = new RasterizerState();
	_rasterizerState->SetState();
}

void StateManager::CreateBlendState()
{
	_blendStates.emplace_back(new BlendState());
	_blendStates.emplace_back(new BlendState());
	_blendStates.emplace_back(new BlendState());

	_blendStates[1]->Alpha(true);
	_blendStates[2]->Additive();
}

void StateManager::CreateDepthStencilState()
{
	_depthStencilStates.emplace_back(new DepthStencilState());
	_depthStencilStates.emplace_back(new DepthStencilState());
	_depthStencilStates.emplace_back(new DepthStencilState());

	_depthStencilStates[1]->DepthEnable(false);
}

void StateManager::AlphaBegin()
{
	_blendStates[1]->SetState();
}

void StateManager::AlphaEnd()
{
	_blendStates[0]->SetState();
}

void StateManager::DepthEnable()
{
	_depthStencilStates[0]->SetState();
}

void StateManager::DepthDisable()
{
	_depthStencilStates[1]->SetState();
}

void StateManager::Set()
{
	AlphaEnd();
	DepthEnable();
}

void StateManager::PostSet()
{
	AlphaBegin();
	DepthDisable();
}

