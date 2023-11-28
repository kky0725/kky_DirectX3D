#include "Framework.h"
#include "Shadow.h"

Shadow::Shadow(UINT width, UINT height)
	:_width(width), _height(height)
{
	_renderTarget = new RenderTarget(10000, 10000);
	_depthStencil = new DepthStencil(width, height);

	_viewBuffer = new ViewBuffer();
	_projBuffer = new MatrixBuffer();

	_quad = new Quad(Vector2(200, 200));
	_quad->_translation = { 100, 100, 0 };

	Texture* texture = Texture::Get(L"DepthMap", _renderTarget->GetSRV());
	_quad->GetMaterial()->SetDiffuseMap(texture);
	_quad->Update();
}

Shadow::~Shadow()
{
	delete _renderTarget;
	delete _depthStencil;
	delete _viewBuffer;
	delete _projBuffer;
	delete _quad;
}

void Shadow::SetPreRender()
{
	_renderTarget->Set(_depthStencil);
	SetViewProjection();
}

void Shadow::SetRender()
{
	_viewBuffer->SetVSBuffer(11);
	_projBuffer->SetVSBuffer(12);

	DC->PSGetShaderResources(10, 1, &_renderTarget->GetSRV());
}

void Shadow::PostRender()
{
	_quad->Render();
}

void Shadow::SetViewProjection()
{
	LightBuffer::LightData& lightData = Environment::GetInstance()->GetLightBuffer()->data.lights[0];
	
	Matrix view = XMMatrixLookAtLH(lightData.position, Vector3(0, 0, 0), Vector3(0, 1, 0));

	Matrix proj = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1.0f, 0.1f, 5000.0f);

	_viewBuffer->SetData(view, XMMatrixInverse(nullptr, view));
	_projBuffer->SetData(proj);

	_viewBuffer->SetVSBuffer(1);
	_projBuffer->SetVSBuffer(2);
}