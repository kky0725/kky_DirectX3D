#pragma once
class GeomtryBuffer
{
	enum RnderTargets
	{
		DIFFUSE,
		NORMAL,
		SPECULAR,
		SIZE
	};

public:
	GeomtryBuffer();
	~GeomtryBuffer();

	void SetMultiRenderTarget();
	void PostRender();
	void SetSRVs();

private:
	DepthStencil* _depthStencil;

	RenderTarget* _rtvs[SIZE];

	class Quad* _quads[SIZE + 1];
	ID3D11ShaderResourceView* _srvs[SIZE + 1];
};