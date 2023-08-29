#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singleton;
	StateManager();
	~StateManager();

	void CreateSamplerState();

public:


private:
	SamplerState* _samplerStae = nullptr;
};