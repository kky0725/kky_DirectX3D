#include "Framework.h"
#include "StateManager.h"

StateManager::StateManager()
{
	CreateSamplerState();
	CreateRasterizerState();
	CreateBlendState();
}

StateManager::~StateManager()
{
	delete _samplerStae;
	delete _rasterizerState;

	for (BlendState* blend : _blendStates)
		delete blend;
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

void StateManager::AlphaBegin()
{
	_blendStates[1]->SetState();
}

void StateManager::AlphaEnd()
{
	_blendStates[0]->SetState();
}

