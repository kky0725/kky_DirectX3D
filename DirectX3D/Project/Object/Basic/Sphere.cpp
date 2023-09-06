#include "Framework.h"
#include "Sphere.h"

Sphere::Sphere(float radius, UINT latitudes, UINT longitudes)
	:_radius(radius), _latitudes(latitudes), _longitudes(longitudes)
{
	CreateMesh();
	_mesh = new Mesh(_vertices, _indices);
	_material = new Material(L"Specular");

	_worldBuffer = new MatrixBuffer();
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

void Sphere::CreateMesh()
{
	for (int i = 0; i <= _latitudes; i++)//stack
	{
		float thetaI = i * XM_PI / _latitudes;
		for (int j = 0; j <= _longitudes; j++)//slice
		{
			VertexType vertex;
			float thetaJ = j * XM_2PI / _longitudes;

			vertex.pos.x = _radius * sin(thetaI) * cos(thetaJ);
			vertex.pos.y = _radius * cos(thetaI);
			vertex.pos.z = _radius * sin(thetaI) * sin(thetaJ);

			vertex.normal.x = sin(thetaI) * cos(thetaJ);
			vertex.normal.y = cos(thetaI);
			vertex.normal.z = sin(thetaI) * sin(thetaJ);

			//vertex.normal = vertex.pos / _radius;

			vertex.uv.x = j / (float)_longitudes;
			vertex.uv.y = i / (float)_latitudes;

			_vertices.push_back(vertex);
		}
	}

	for (int i = 0; i < _latitudes; i++)//stack
	{
		for (int j = 0; j < _longitudes; j++)//slice
		{
			UINT LB = j + 0 + (i + 0) * (_longitudes + 1);
			UINT RB = j + 1 + (i + 0) * (_longitudes + 1);
			UINT LT = j + 0 + (i + 1) * (_longitudes + 1);
			UINT RT = j + 1 + (i + 1) * (_longitudes + 1);
			_indices.push_back(LB);
			_indices.push_back(LT);
			_indices.push_back(RB);

			_indices.push_back(RB);
			_indices.push_back(LT);
			_indices.push_back(RT);
		}
	}
}
