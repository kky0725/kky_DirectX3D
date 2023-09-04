#include "Framework.h"
#include "Cube.h"

int Cube::_count = 0;

Cube::Cube(Vector4 color)
{
	_material = new Material(L"Color");

	_worldBuffer = new MatrixBuffer();

	CreateMesh(color);
	CreateNormal();

	_mesh = new Mesh(_vertices, _indices);

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
		VertexType({ -0.5, +0.5f, -0.5f }, color, {0.0f, 0.0f, 0.0f}),
		VertexType({ +0.5, +0.5f, -0.5f }, color, {0.0f, 0.0f, 0.0f}),
		VertexType({ -0.5, -0.5f, -0.5f }, color, {0.0f, 0.0f, 0.0f}),
		VertexType({ +0.5, -0.5f, -0.5f }, color, {0.0f, 0.0f, 0.0f}),

		VertexType({ -0.5, +0.5f, +0.5f }, color, {0.0f, 0.0f, 0.0f}),
		VertexType({ +0.5, +0.5f, +0.5f }, color, {0.0f, 0.0f, 0.0f}),
		VertexType({ -0.5, -0.5f, +0.5f }, color, {0.0f, 0.0f, 0.0f}),
		VertexType({ +0.5, -0.5f, +0.5f }, color, {0.0f, 0.0f, 0.0f})
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

}

void Cube::CreateNormal()
{
	for (UINT i = 0; i < _indices.size() / 3; i++)
	{
		UINT index0 = _indices[i * 3 + 0];
		UINT index1 = _indices[i * 3 + 1];
		UINT index2 = _indices[i * 3 + 2];

		Vector3 p0 = _vertices[index0].pos;
		Vector3 p1 = _vertices[index1].pos;
		Vector3 p2 = _vertices[index2].pos;

		Vector3 v01 = p1 - p0;
		Vector3 v02 = p2 - p0;

		Vector3 normal = Vector3::Cross(v01, v02).GetNormalized();

		_vertices[index0].normal += normal;
		_vertices[index1].normal += normal;
		_vertices[index2].normal += normal;
	}
}

