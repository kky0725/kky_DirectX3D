#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
	CreateViewport();
	CreatePerspective();
	CreateOrthographic();

	_lightBuffer = new LightBuffer();
}

Environment::~Environment()
{
	delete _lightBuffer;
	delete _persBuffer;
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
	_persBuffer = new MatrixBuffer();

	_PersMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);

	_persBuffer->SetData(_PersMatrix);
}

void Environment::CreateOrthographic()
{
	_orthoBuffer = new MatrixBuffer();

	_orthoMatrix = XMMatrixOrthographicOffCenterLH(0.0f, WIN_WIDTH, 0.0f, WIN_HEIGHT, -1.0f, 1.0f);

	_orthoBuffer->SetData(_orthoMatrix);

	_UIViewBuffer = new ViewBuffer();
}

void Environment::SetEnvironment()
{
	_lightBuffer->SetPSBuffer(0);//header.hlsl 문제 해결하면 0으로 변경
	_persBuffer->SetVSBuffer(2);

	StateManager::GetInstance()->Set();
}

void Environment::PostSet()
{
	_UIViewBuffer->SetVSBuffer(1);
	_orthoBuffer->SetVSBuffer(2);

	StateManager::GetInstance()->PostSet();
}

void Environment::PostRneder()
{
	ImGui::SliderFloat3("LightDirection", (float*)&_lightBuffer->data.direction, -1.0f, +1.0f);
	ImGui::ColorEdit4("AmbientLight", (float*)&_lightBuffer->data.ambientLight);
}

