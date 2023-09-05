#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singleton;
	StateManager();
	~StateManager();

	void CreateSamplerState();
	void CreateRasterizerState();

public:
	RasterizerState* GetRS() { return _rasterizerState; }


private:
	SamplerState* _samplerStae = nullptr;
	RasterizerState* _rasterizerState = nullptr;
};