#include "Framework.h"
#include "Sphere.h"

Sphere::Sphere(Vector4 color, float radius)
	:_radius(radius)
{
	_material = new Material(L"DiffuseColor");

	_worldBuffer = new MatrixBuffer();

	CreateMesh(color);
	//CreateNormal();

	_mesh = new Mesh(_vertices, _indices);
}

Sphere::~Sphere()
{
	delete _mesh;
	delete _material;
	delete _worldBuffer;
}

void Sphere::Update()
{
	Transform::Update();

	_worldBuffer->SetData(_world);
}

void Sphere::Render()
{
	_material->SetMaterial();
	_mesh->SetMesh();

	_worldBuffer->SetVSBuffer(0);

	DC->DrawIndexed(_indices.size(), 0, 0);
}

void Sphere::CreateMesh(Vector4 color)
{
	for (int i = 0; i <= _latitudes; i++)
	{
		float thetaI = i * XM_PI / _latitudes;
		for (int j = 0; j <= _longitudes; j++)
		{
			VertexColorNormal vertex;
			float thetaJ = j * 2 * XM_PI / _longitudes;

			vertex.pos.x = _radius * sin(thetaI) * cos(thetaJ);
			vertex.pos.y = _radius * cos(thetaI);
			vertex.pos.z = _radius * sin(thetaI) * sin(thetaJ);

			vertex.normal.x = sin(thetaI) * cos(thetaJ);
			vertex.normal.y = cos(thetaI);
			vertex.normal.z = sin(thetaI) * sin(thetaJ);

			vertex.color = color;

			_vertices.push_back(vertex);
		}
	}

	for (int i = 0; i < _latitudes; i++)
	{
		for (int j = 0; j < _longitudes; j++)
		{
			UINT LB = j + 0 + (i + 0) * (_longitudes + 1);
			UINT RB = j + 1 + (i + 0) * (_longitudes + 1);
			UINT LT = j + 0 + (i + 1) * (_longitudes + 1);
			UINT RT = j + 1 + (i + 1) * (_longitudes + 1);
			_indices.push_back(LT);
			_indices.push_back(RT);
			_indices.push_back(LB);
			_indices.push_back(LB);
			_indices.push_back(RT);
			_indices.push_back(RB);
		}
	}
}

void Sphere::CreateNormal()
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
