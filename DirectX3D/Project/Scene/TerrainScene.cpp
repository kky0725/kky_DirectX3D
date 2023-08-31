#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	_material = new Material();
	_material->SetShader(L"Texture");
	_material->SetDiffuseMap(L"Landscape/Dirt.png");

	_worldBuffer = new MatrixBuffer();

	_heightMap = Texture::Get(L"HeightMap/HeightMap.png");

	CreateMesh();
}

TerrainScene::~TerrainScene()
{
	delete _mesh;
	delete _worldBuffer;
	delete _material;
}

void TerrainScene::Update()
{
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	_worldBuffer->SetVSBuffer(0);
	
		_mesh->SetMesh();
	_material->SetMaterial();

	DC->DrawIndexed(_indices.size(), 0, 0);
}

void TerrainScene::PostRender()
{
}

void TerrainScene::CreateMesh()
{
	 _width = _heightMap->GetSize().x;
	_height = _heightMap->GetSize().y;

	vector<Vector4> colors = _heightMap->ReadPixels();

	//Vertex
	for (float z = 0; z < _height; z++)
	{
		for (float x = 0; x < _width; x++)
		{
			VertexTexture vertex;
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

	_mesh = new Mesh(_vertices, _indices);
}

