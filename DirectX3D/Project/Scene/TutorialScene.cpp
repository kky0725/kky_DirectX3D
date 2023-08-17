#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_vertexShader = Shader::GetVS(L"Tutorial");
	 _pixelShader = Shader::GetPS(L"Tutorial");



	/// ///////////////////



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
	_vertexBuffer = new VertexBuffer(vertices);

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

	_indexBuffer = new IndexBuffer(indices);

	//WVP

	_worldBuffer = new MatrixBuffer();
	_viewBuffer = new MatrixBuffer();
	_projectionBuffer = new MatrixBuffer();

	XMVECTOR eyePos = XMVectorSet(+3.0f, +3.0f, -3.0f, 1.0f);
	XMVECTOR focusPos = XMVectorSet(+0.0f, +0.0f, +0.0f, 1.0f);
	XMVECTOR upVector = XMVectorSet(+0.0f, +1.0f, +0.0f, 0.0f);

	XMMATRIX view = XMMatrixLookAtLH(eyePos, focusPos, upVector);

	_viewBuffer->SetData(view);

	XMMATRIX projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);

	_projectionBuffer->SetData(projection);
}

TutorialScene::~TutorialScene()
{
	delete _vertexBuffer;
	delete _indexBuffer;

	delete _worldBuffer;
	delete _viewBuffer;
	delete _projectionBuffer;
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
	_vertexShader->SetShader();
	_pixelShader->SetShader();

	_vertexBuffer->IASetBuffer();
	_indexBuffer->IASetBuffer();


	_worldBuffer->SetVSBuffer(0);
	_viewBuffer->SetVSBuffer(1);
	_projectionBuffer->SetVSBuffer(2);

	DC->DrawIndexed(indices.size(), 0, 0);

	//WVP
	static float angle = 0.0f;
	angle += 0.0001f;

	XMMATRIX world = XMMatrixRotationRollPitchYaw(angle, angle, 0.0f);
	_worldBuffer->SetData(world);

}

void TutorialScene::PostRender()
{
}
