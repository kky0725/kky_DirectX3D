#include "Framework.h"
#include "GridScene.h"

GridScene::GridScene()
{
	_material = new Material(L"Tutorial");

	_worldBuffer = new WorldBuffer();

	CreateMesh();
}

GridScene::~GridScene()
{
	delete _worldBuffer;
	delete _material;
	delete _vertexBuffer;
}

void GridScene::Update()
{
}

void GridScene::PreRender()
{
}

void GridScene::Render()
{
	_worldBuffer->SetVSBuffer(0);
	_material->SetMaterial();
	_vertexBuffer->IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	DC->Draw(_vertices.size(), 0);
}

void GridScene::PostRender()
{
}

void GridScene::CreateMesh()
{
	_vertices.emplace_back(-_width, 0, 0, 1, 0, 0, 1);
	_vertices.emplace_back(+_width, 0, 0, 1, 0, 0, 1);

	_vertices.emplace_back(0, -_width, 0, 0, 1, 0, 1);
	_vertices.emplace_back(0, +_width, 0, 0, 1, 0, 1);

	_vertices.emplace_back(0, 0, -_width, 0, 0, 1, 1);
	_vertices.emplace_back(0, 0, +_width, 0, 0, 1, 1);

	int halfW = _width * 0.5f;
	int halfH = _height * 0.5f;

	for (int x = -halfW; x < halfW; x++)
	{
		if (x == 0)
			continue;

		_vertices.emplace_back(x, 0, -halfW, 0.5f, 0.5f, 0.5f, 1.0f);
		_vertices.emplace_back(x, 0, +halfW, 0.5f, 0.5f, 0.5f, 1.0f);
	}

	for (int z = -halfH; z < halfH; z++)
	{
		if (z == 0)
			continue;

		_vertices.emplace_back(-halfH, 0, z, 0.5f, 0.5f, 0.5f, 1.0f);
		_vertices.emplace_back(+halfH, 0, z, 0.5f, 0.5f, 0.5f, 1.0f);
	}


	_vertexBuffer = new VertexBuffer(_vertices);
}


