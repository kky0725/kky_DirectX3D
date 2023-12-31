#include "Framework.h"
#include "Terrain.h"

Terrain::Terrain(wstring diffuseFile, wstring heightFile)
{
	_material = new Material();
	//_material->SetShader(L"Diffuse");
	//_material->SetShader(L"Specular");
	_material->SetShader(L"09Light");
	_material->SetDiffuseMap(diffuseFile);

	//_material->SetDiffuseMap(L"Landscape/Wall.png");
	//_material->SetSpecularMap(L"Landscape/Wall_specular.png");
	//_material->SetNormalMap(L"Landscape/Wall_normal.png");

	//_material->SetDiffuseMap(L"Landscape/Fieldstone_DM.tga");
	//_material->SetSpecularMap(L"Landscape/Fieldstone_SM.tga");
	//_material->SetNormalMap(L"Landscape/Fieldstone_NM.tga");


	_heightMap = Texture::Get(heightFile);

	CreateMesh();
	CreateNormal();
	CreateTangent();
	_mesh = new Mesh(_vertices, _indices);
}

Terrain::~Terrain()
{
	delete _mesh;
	delete _material;
}

void Terrain::Render()
{
	Transform::SetWorld();

	_mesh->SetMesh();
	_material->SetMaterial();

	DC->DrawIndexed(_indices.size(), 0, 0);

	_material->Debug();
}

bool Terrain::Picking(OUT Vector3* position)
{
	Ray ray = CAMERA->ScreenPointToRay(mousePos);

	for (UINT z = 0; z < _height - 1; z++)
	{
		for (UINT x = 0; x < _width - 1; x++)
		{
			UINT index[4];
			index[0] = (x + 0) + _width * (z + 0);
			index[1] = (x + 1) + _width * (z + 0);
			index[2] = (x + 0) + _width * (z + 1);
			index[3] = (x + 1) + _width * (z + 1);

			Vector3 pos[4];
			for (int i = 0; i < 4; i++)
			{
				pos[i] = _vertices[index[i]].pos;
			}

			float distance = 0.0f;

			if (TriangleTests::Intersects(ray.origin, ray.direction, pos[0], pos[1], pos[2], distance))
			{
				*position = ray.origin + ray.direction * distance;
				return true;
			}

			if (TriangleTests::Intersects(ray.origin, ray.direction, pos[3], pos[1], pos[2], distance))
			{
				*position = ray.origin + ray.direction * distance;
				return true;
			}
		}
	}

	return false;
}

float Terrain::GetHeight(Vector3 position)
{
	position.x /= _scale.x;
	position.z /= _scale.z;

	int x = (int)position.x;
	int z = (int)position.z;

	if (x < 0 || x >= _width - 1 || z < 0 || z >= _height - 1)
		return 0;

	UINT index[4];
	index[0] = x + 0 + _width * (z + 1);
	index[1] = x + 1 + _width * (z + 1);
	index[2] = x + 0 + _width * (z + 0);
	index[3] = x + 1 + _width * (z + 0);

	Vector3 vertex[4];
	for (UINT i = 0; i < 4; i++)
	{
		vertex[i] = _vertices[index[i]].pos;
	}

	float u = position.x - vertex[0].x;
	float v = position.z - vertex[0].z;
	v = abs(v);

	Vector3 result;

	if (u + v <= 1.0f)
	{
		result = vertex[0] + (vertex[2] - vertex[0]) * u + (vertex[1] - vertex[0]) * v;
	}
	else
	{
		u = 1 - u;
		v = 1 - v;
		result = vertex[3] + (vertex[2] - vertex[3]) * u + (vertex[1] - vertex[3]) * v;
	}

	return result.y * _scale.y;
}

void Terrain::CreateMesh()
{
	 _width = _heightMap->GetSize().x;
	_height = _heightMap->GetSize().y;

	vector<Vector4> colors = _heightMap->ReadPixels();

	//Vertex
	for (float z = 0; z < _height; z++)
	{
		for (float x = 0; x < _width; x++)
		{
			VertexType vertex;
			vertex.pos = Vector3(x, 0, z);

			vertex.uv.x =	  x / (_width  - 1);
			vertex.uv.y = 1 - z / (_height - 1);

			//HeightMap
			UINT index = x + z * _width;
			vertex.pos.y = colors[index].x * MAP_HEIGHT;

			_vertices.push_back(vertex);
		}
	}

	//Indices
	for (float z = 0; z < _height - 1; z++)
	{
		for (float x = 0; x < _width - 1; x++)
		{
			UINT LB = x + 0 + (z + 0) * _width;
			UINT RB = x + 1 + (z + 0) * _width;
			UINT LT = x + 0 + (z + 1) * _width;
			UINT RT = x + 1 + (z + 1) * _width;
			_indices.push_back(LT);
			_indices.push_back(RT);
			_indices.push_back(LB);
			_indices.push_back(LB);
			_indices.push_back(RT);
			_indices.push_back(RB);
		}
	}
}

void Terrain::CreateNormal()
{
	for (UINT i = 0; i < _indices.size() /3; i++)
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

void Terrain::CreateTangent()
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


