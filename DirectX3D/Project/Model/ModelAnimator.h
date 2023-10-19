#pragma once
class ModelAnimator : public Transform
{
public:
	ModelAnimator(string name, wstring shaderFile = L"02ModelAnimation");
	~ModelAnimator();

	void Update();
	void Render();

	void ReadClip(string file, UINT clipIndex = 0);
	void PlayClip(UINT clipIndex, float speed = 1.0f, float takeTime = 2.0f);

	void CreateTexture();
	
	void UpdateFrame();

private:
	void CreateClipTransform(UINT index);

private:
	ModelReader*		_reader;
	vector<ModelClip*>	_clips;
	string				_name;

	FrameBuffer* _frameBuffer;

	ClipTransform* _clipTransform;
	ClipTransform* _nodeTransform;

	ID3D11Texture2D*			_texture;
	ID3D11ShaderResourceView*	_srv;
};