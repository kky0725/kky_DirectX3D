#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singleton;
	StateManager();
	~StateManager();

	void CreateSamplerState();
	void CreateRasterizerState();

public:


private:
	SamplerState* _samplerStae = nullptr;
	RasterizerState* _rasterizerState = nullptr;
};