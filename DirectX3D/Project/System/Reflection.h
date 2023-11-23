#pragma once
class Reflection
{
public:
	Reflection(Transform* target);
	~Reflection();

	void Update();

	void SetPreRender();
	void SetRender();

	void PostRender();

private:
	Transform* _target;

	RenderTarget* _renderTarget;
	DepthStencil* _depthStencil;

	Camera* _camera;
	Quad* _quad;

	static UINT _index;
};