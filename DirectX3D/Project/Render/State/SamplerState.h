#pragma once
class SamplerState
{
public:
	SamplerState();
	~SamplerState();

private:
	ID3D11SamplerState* _samplerState = nullptr;
};