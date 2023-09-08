#include "Framework.h"
#include "Terrain.h"

Terrain::Terrain(wstring diffuseFile, wstring heightFile)
{
	_material = new Material();
	//_material->SetShader(L"Diffuse");
	//_material->SetShader(L"Specular");
	_material->SetShader(L"NormalMapping");
	//_material->SetDiffuseMap(diffuseFile);

	//_material->SetDiffuseMap(L"Landscape/Wall.png");
	//_material->SetSpecularMap(L"Landscape/Wall_specular.png");
	//_material->SetNormalMap(L"Landscape/Wall_normal.png");

	_material->SetDiffuseMap(L"Landscape/Fieldstone_DM.tga");
	_material->SetSpecularMap(L"Landscape/Fieldstone_SM.tga");
	_material->SetNormalMap(L"Landscape/Fieldstone_NM.tga");

	_worldBuffer = new MatrixBuffer();

	_heightMap = Texture::Get(heightFile);

	CreateMesh();
	CreateNormal();
	CreateTangent();
	_mesh = new Mesh(_vertices, _indices);
}

Terrain::~Terrain()
{
	delete _mesh;
	delete _worldBuffer;
	delete _material;
}

void Terrain::Render()
{
	_worldBuffer->SetVSBuffer(0);

	_mesh->SetMesh();
	_material->SetMaterial();

	DC->DrawIndexed(_indices.size(), 0, 0);

	_material->PostRender();
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


