#include "Framework.h"
#include "StateManager.h"

StateManager::StateManager()
{
	CreateSamplerState();
}

StateManager::~StateManager()
{
	delete _samplerStae;
}

void StateManager::CreateSamplerState()
{
	_samplerStae = new SamplerState();
}

