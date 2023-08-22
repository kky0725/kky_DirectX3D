#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
	CreateViewport();
	CreatePerspective();
}

Environment::~Environment()
{
	delete _viewBuffer;
	delete _projectionBuffer;
}

void Environment::CreateViewport()
{
	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = WIN_WIDTH;
	viewPort.Height = WIN_HEIGHT;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	DC->RSSetViewports(1, &viewPort);
}

void Environment::CreatePerspective()
{
	_viewBuffer = new MatrixBuffer();
	_projectionBuffer = new MatrixBuffer();

	//XMVECTOR eyePos = XMVectorSet(+3.0f, +3.0f, -3.0f, 1.0f);
	XMVECTOR eyePos = XMVectorSet(+0.0f, +0.0f, -3.0f, 1.0f);
	XMVECTOR focusPos = XMVectorSet(+0.0f, +0.0f, +0.0f, 1.0f);
	XMVECTOR upVector = XMVectorSet(+0.0f, +1.0f, +0.0f, 0.0f);

	XMMATRIX view = XMMatrixLookAtLH(eyePos, focusPos, upVector);

	_viewBuffer->SetData(view);

	XMMATRIX projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);

	_projectionBuffer->SetData(projection);

	_viewBuffer->SetVSBuffer(1);
	_projectionBuffer->SetVSBuffer(2);
}

