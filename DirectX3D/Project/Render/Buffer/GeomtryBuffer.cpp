#include "Framework.h"
#include "GeomtryBuffer.h"

GeomtryBuffer::GeomtryBuffer()
{
	for (UINT i = 0; i < SIZE; i++)
	{
		_rtvs[i] = new RenderTarget;
		_srvs[i] = _rtvs[i]->GetSRV();
	}

	_depthStencil = new DepthStencil(WIN_WIDTH, WIN_HEIGHT, true);
	_srvs[SIZE] = _depthStencil->GetSRV();

	for (UINT i = 0; i < SIZE + 1; i++)
	{
		_quads[i] = new Quad(Vector2(200, 200));
		_quads[i]->_translation =Vector3(100 + i * 200, 100, 0);

		Texture* texture = Texture::Get(L"G" + to_wstring(i), _srvs[i]);
		_quads[i]->GetMaterial()->SetDiffuseMap(texture);
		_quads[i]->UpdateWorld();
	}
}

GeomtryBuffer::~GeomtryBuffer()
{
	delete _depthStencil;

	for (UINT i = 0; i < SIZE; i++)
	{
		delete _rtvs[i];
	}

	for (UINT i = 0; i < SIZE + 1; i++)
	{
		delete _quads[i];
	}
}

void GeomtryBuffer::SetMultiRenderTarget()
{
	RenderTarget::SetMulti(_rtvs, SIZE, _depthStencil, Vector4(1, 1, 0, 1));
}

void GeomtryBuffer::PostRender()
{
	for (Quad* quad : _quads)//È®ÀÎ¿ë
		quad->Render();
}

void GeomtryBuffer::SetSRVs()
{
	for (UINT i = 0; i < SIZE + 1; i++)
	{
		DC->PSSetShaderResources(10 + i, 1, &_srvs[i]);
	}
}


