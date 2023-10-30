#pragma once
class BlendState
{
public:
	BlendState();
	~BlendState();

	void SetState();
	void ChangeState();

	void Alpha(bool value);
	void AlphaToCoverage(bool value);
	void Additive();

private:
	D3D11_BLEND_DESC _desc = {};
	ID3D11BlendState* _state = nullptr;
};