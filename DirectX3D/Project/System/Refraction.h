#pragma once
class Refraction
{
public:
	Refraction(wstring file);
	~Refraction();

	void Update();

	void SetPreRender();
	void SetRender();

	void PostRender();
	void DeBug();

private:
	class Quad* _quad;

	RenderTarget* _renderTarget;
	DepthStencil* _depthStencil;

	Texture* _normalMap;

	static UINT _index;

	WaterBuffer* _buffer;
};