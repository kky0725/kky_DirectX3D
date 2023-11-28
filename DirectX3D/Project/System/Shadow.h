#pragma once
class Shadow
{
public:
	Shadow(UINT width = 2000, UINT height = 2000);
	~Shadow();

	void SetPreRender();
	void SetRender();
	void PostRender();

private:
	void SetViewProjection();

private:
	UINT _width, _height;

	RenderTarget* _renderTarget;
	DepthStencil* _depthStencil;

	ViewBuffer*		_viewBuffer;
	MatrixBuffer*	_projBuffer;
	
	Quad* _quad;//debug¿ë
};