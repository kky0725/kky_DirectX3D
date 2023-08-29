#include "Framework.h"
#include "Cube.h"

int Cube::_count = 0;

Cube::Cube(Vector4 color)
{
	_material = new Material(L"Tutorial");

	CreateMesh(color);

	_worldBuffer = new MatrixBuffer();

	_count++;

	_label = "Cube" + to_string(_count);
}

Cube::~Cube()
{
	delete _mesh;
	delete _material;

	delete _worldBuffer;
}

void Cube::Update()
{
	Transform::Update();

	_worldBuffer->SetData(_world);
}

void Cube::Render()
{
	//todo: Render
	_material->SetMaterial();
	_mesh->SetMesh();

	_worldBuffer->SetVSBuffer(0);

	DC->DrawIndexed(_indices.size(), 0, 0);
	
}

void Cube::CreateMesh(Vector4 color)
{
	_vertices =
	{
		VertexColor({ -1.0f, +1.0f, -1.0f }, color),
		VertexColor({ +1.0f, +1.0f, -1.0f }, color),
		VertexColor({ -1.0f, -1.0f, -1.0f }, color),
		VertexColor({ +1.0f, -1.0f, -1.0f }, color),

		VertexColor({ -1.0f, +1.0f, +1.0f }, color),
		VertexColor({ +1.0f, +1.0f, +1.0f }, color),
		VertexColor({ -1.0f, -1.0f, +1.0f }, color),
		VertexColor({ +1.0f, -1.0f, +1.0f }, color)
	};

	_indices =
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

	_mesh = new Mesh(_vertices, _indices);
}

