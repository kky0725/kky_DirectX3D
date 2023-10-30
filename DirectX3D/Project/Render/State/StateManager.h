#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singleton;
	StateManager();
	~StateManager();

	void CreateSamplerState();
	void CreateRasterizerState();
	void CreateBlendState();

public:
	RasterizerState* GetRS() { return _rasterizerState; }

	void AlphaBegin();
	void AlphaEnd();

private:
	SamplerState* _samplerStae = nullptr;
	RasterizerState* _rasterizerState = nullptr;

	vector<BlendState*> _blendStates;
};