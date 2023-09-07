#include "Framework.h"
#include "Terrain.h"

Terrain::Terrain(wstring diffuseFile, wstring heightFile)
{
	_material = new Material();
	//_material->SetShader(L"Diffuse");
	_material->SetShader(L"Specular");
	//_material->SetDiffuseMap(diffuseFile);

	_material->SetDiffuseMap(L"Landscape/Wall.png");
	_material->SetSpecularMap(L"Landscape/Wall_specular.png");

	_worldBuffer = new MatrixBuffer();

	_heightMap = Texture::Get(heightFile);

	CreateMesh();
	CreateNormal();
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
			VertexTextureNormal vertex;
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


