#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singleton;
	StateManager();
	~StateManager();

	void CreateSamplerState();
	void CreateRasterizerState();
	void CreateBlendState();
	void CreateDepthStencilState();

public:
	RasterizerState* GetRS() { return _rasterizerState; }

	void AlphaBegin();
	void AlphaEnd();

	void DepthEnable();
	void DepthDisable();
	
	void Set();
	void PostSet();

private:
	SamplerState* _samplerStae = nullptr;
	RasterizerState* _rasterizerState = nullptr;

	vector<BlendState*> _blendStates;

	vector<DepthStencilState*> _depthStencilStates;
};