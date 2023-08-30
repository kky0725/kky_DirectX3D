#include "Framework.h"
#include "StateManager.h"

StateManager::StateManager()
{
	CreateSamplerState();
	CreateRasterizerState();
}

StateManager::~StateManager()
{
	delete _samplerStae;
	delete _rasterizerState;
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

