#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	/// ///////////////////

	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = WIN_WIDTH;
	viewPort.Height = WIN_HEIGHT;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	DC->RSSetViewports(1, &viewPort);


	//VertexShader

	// pixelShader

	//Vertex
	//Vertex vertex(0.0f, 0.0f, 0.0f);

	vertices =
	{
		VertexColor({-1.0f, +1.0f, -1.0f}, {1.0f, 0.0f, 0.0f ,1.0f}),
		VertexColor({+1.0f, +1.0f, -1.0f}, {0.0f, 1.0f, 0.0f ,1.0f}),
		VertexColor({-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f ,1.0f}),
		VertexColor({+1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 0.0f ,1.0f}),

		VertexColor({-1.0f, +1.0f, +1.0f}, {1.0f, 0.0f, 0.0f ,1.0f}),
		VertexColor({+1.0f, +1.0f, +1.0f}, {0.0f, 1.0f, 0.0f ,1.0f}),
		VertexColor({-1.0f, -1.0f, +1.0f}, {0.0f, 0.0f, 1.0f ,1.0f}),
		VertexColor({+1.0f, -1.0f, +1.0f}, {1.0f, 1.0f, 0.0f ,1.0f})
	};

	//VertexBuffer
	{
		D3D11_BUFFER_DESC bufferDesc = {};

		bufferDesc.ByteWidth = sizeof(VertexColor) * vertices.size();
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA data;

		data.pSysMem = vertices.data();

		DEVICE->CreateBuffer(&bufferDesc, &data, &vertexBuffer);
	}

	//IndexBuffer

	indices =
	{
		//Front
		0, 1, 2,
		2, 1, 3,

		//Right
		1, 5, 3,
		3, 5, 7,

		//Top
		0, 4, 1,
		1, 4, 5,

		//Left
		4, 0, 6,
		6, 0, 2,

		//Back
		5, 4, 7,
		7, 4, 6,

		//Bottom
		2, 3, 6,
		6, 3, 7

	};

	{
		D3D11_BUFFER_DESC bufferDesc = {};

		bufferDesc.ByteWidth = sizeof(UINT) * indices.size();
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA data;

		data.pSysMem = indices.data();

		DEVICE->CreateBuffer(&bufferDesc, &data, &indexBuffer);
	}

	//WVP

	wvp.world = XMMatrixIdentity();

	XMVECTOR eyePos = XMVectorSet(+3.0f, +3.0f, -3.0f, 1.0f);
	XMVECTOR focusPos = XMVectorSet(+0.0f, +0.0f, +0.0f, 1.0f);
	XMVECTOR upVector = XMVectorSet(+0.0f, +1.0f, +0.0f, 0.0f);

	wvp.view = XMMatrixLookAtLH(eyePos, focusPos, upVector);

	wvp.projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);

	{
		D3D11_BUFFER_DESC bufferDesc = {};

		bufferDesc.ByteWidth = sizeof(WVP);
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		DEVICE->CreateBuffer(&bufferDesc, nullptr, &constBuffer);
	}
}

TutorialScene::~TutorialScene()
{

}

void TutorialScene::Update()
{
}

void TutorialScene::PreRender()
{
}

void TutorialScene::Render()
{
	//todo: Render

	stride = sizeof(VertexColor);
	offset = 0;

	DC->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	DC->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	DC->DrawIndexed(indices.size(), 0, 0);

	//WVP
	WVP data;

	data.world = XMMatrixTranspose(wvp.world);
	data.view = XMMatrixTranspose(wvp.view);
	data.projection = XMMatrixTranspose(wvp.projection);

	DC->UpdateSubresource(constBuffer, 0, nullptr, &data, 0, 0);
	DC->VSSetConstantBuffers(0, 1, &constBuffer);

	static float angle = 0.0f;
	angle += 0.0001f;

	wvp.world = XMMatrixRotationRollPitchYaw(angle, angle, 0.0f);

}

void TutorialScene::PostRender()
{
}
