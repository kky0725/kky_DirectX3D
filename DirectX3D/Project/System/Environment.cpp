#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
	CreateViewport();
	CreatePerspective();

	_lightBuffer = new LightBuffer();
}

Environment::~Environment()
{
	delete _lightBuffer;
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
	_projectionBuffer = new MatrixBuffer();

	XMMATRIX projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);

	_projectionBuffer->SetData(projection);

	_projectionBuffer->SetVSBuffer(2);
}

void Environment::SetEnvironment()
{
	_lightBuffer->SetVSBuffer(3);

	_lightBuffer->SetData(_lightDirection);
}

void Environment::PostRneder()
{
	ImGui::SliderFloat3("LightDirection", (float*)&_lightDirection, -1.0f, +1.0f);

}

