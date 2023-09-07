#include "Framework.h"
#include "Sphere.h"

Sphere::Sphere(float radius, UINT latitudes, UINT longitudes)
	:_radius(radius), _latitudes(latitudes), _longitudes(longitudes)
{
	CreateMesh();
	CreateTangent();
	_mesh = new Mesh(_vertices, _indices);

	//_material = new Material(L"Specular");
	_material = new Material(L"NormalMapping");

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

void Sphere::CreateTangent()
{
	for (UINT i = 0; i < _indices.size() / 3; i++)
	{
		UINT index0 = _indices[i * 3 + 0];
		UINT index1 = _indices[i * 3 + 1];
		UINT index2 = _indices[i * 3 + 2];

		Vector3 p0 = _vertices[index0].pos;
		Vector3 p1 = _vertices[index1].pos;
		Vector3 p2 = _vertices[index2].pos;

		Vector2 uv0 = _vertices[index0].uv;
		Vector2 uv1 = _vertices[index1].uv;
		Vector2 uv2 = _vertices[index2].uv;

		Vector3 e01 = p1 - p0;
		Vector3 e02 = p2 - p0;

		float u1 = uv1.x - uv0.x;
		float v1 = uv1.y - uv0.y;

		float u2 = uv2.x - uv0.x;
		float v2 = uv2.y - uv0.y;

		float D = 1.0f / (u1 * v2 - v1 * u2);

		Vector3 tangent = D * (e01 * v2 - e02 * v1);

		_vertices[index0].tangent += tangent;
		_vertices[index1].tangent += tangent;
		_vertices[index2].tangent += tangent;
	}

	for (VertexType& vertex : _vertices)
	{
		Vector3 T = vertex.tangent;
		Vector3 N = vertex.normal;

		vertex.tangent = (T - N * Vector3::Dot(N, T)).GetNormalized();
	}
}
