#include "Framework.h"
#include "TerrainLOD.h"

TerrainLOD::TerrainLOD(wstring heightMap)
{
	_material = new Material(L"24TerrainLOD");
	_material->SetDiffuseMap(L"LandScape/Dirt2.png");

	_hullShader = Shader::GetHS(L"24TerrainLOD");
	_domainShader = Shader::GetDS(L"24TerrainLOD");

	_heightMap = Texture::Get(heightMap);

	_terrainBuffer = new FloatValueBuffer();
	_heightBuffer = new FloatValueBuffer();

	_terrainBuffer->data = { 1.0f, 1000.0f, 1.0f, 64.0f };

	_heightBuffer->data.value[0] = 20.0f;

	CreateMesh();
}

TerrainLOD::~TerrainLOD()
{
	delete _material;
	delete _terrainBuffer;
	delete _heightBuffer;
	delete _mesh;
}

void TerrainLOD::Render()
{
	Transform::SetWorld();

	_terrainBuffer->SetHSBuffer(10);
	_heightBuffer->SetDSBuffer(10);

	_heightMap->DSSetShaderResources(10);

	_material->SetMaterial();
	_mesh->SetMesh(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);

	_hullShader->SetShader();
	_domainShader->SetShader();

	DC->DrawIndexed(_indices.size(), 0, 0);

	DC->HSSetShader(nullptr, nullptr, 0);
	DC->DSSetShader(nullptr, nullptr, 0);
}

void TerrainLOD::Debug()
{
	ImGui::Text("TerrainLOD Option");
	ImGui::DragFloat("MinDistance", &_terrainBuffer->data.value[0]);
	ImGui::DragFloat("MaxDistance", &_terrainBuffer->data.value[1]);
	ImGui::DragFloat("MinQuality ", &_terrainBuffer->data.value[2]);
	ImGui::DragFloat("MaxQuality ", &_terrainBuffer->data.value[3]);


	ImGui::DragFloat("HeightScale", &_heightBuffer->data.value[0]);
}

void TerrainLOD::CreateMesh()
{
	_width = _heightMap->GetSize().x;
	_height = _heightMap->GetSize().y;

	_cellUV = { 1.0f / _width, 1.0f / _height };
	
	_patchWidth  = (_width - 1) / _cellsPerPatch + 1;
	_patchHeight = (_height - 1) / _cellsPerPatch + 1;

	_vertices.resize(_patchWidth * _patchHeight);

	float halfWidth  = _width  * _cellSpacing * 0.5f;
	float halfHeight = _height * _cellSpacing * 0.5f;

	float tempWidth  = _width  * _cellSpacing / _patchWidth;
	float tempHeight = _height * _cellSpacing / _patchHeight;

	float du = 1.0f / _patchWidth;
	float dv = 1.0f / _patchHeight;

	for (UINT z = 0; z < _patchHeight; z++)
	{
		float tempZ = halfHeight - z * tempHeight;
		for (UINT x = 0; x < _patchWidth; x++)
		{
			float tempX = -halfHeight + x * tempHeight;

			UINT index = _patchWidth * z + x;

			_vertices[index].pos = { tempX, 0 , tempZ };
			_vertices[index].uv = { x * du, z * dv };
		}
	}

	_indices.reserve((_patchWidth - 1) * (_patchHeight - 1) * 4);

	for (UINT z = 0; z < _patchHeight - 1; z++)
	{
		for (UINT x = 0; x < _patchWidth - 1; x++)
		{
			_indices.emplace_back(x + 0 + (z + 0) * _patchWidth);
			_indices.emplace_back(x + 1 + (z + 0) * _patchWidth);
			_indices.emplace_back(x + 0 + (z + 1) * _patchWidth);
			_indices.emplace_back(x + 1 + (z + 1) * _patchWidth);
		}
	}

	_mesh = new Mesh(_vertices, _indices);
}
