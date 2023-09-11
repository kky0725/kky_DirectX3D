#include "Framework.h"
#include "TerrainEditor.h"

TerrainEditor::TerrainEditor(UINT height, UINT width)
	: _height(height), _width(width)
{
	_material = new Material();
	_material->SetShader(L"NormalMapping");

	_worldBuffer = new MatrixBuffer();

	CreateMesh();
	CreateNormal();
	CreateTangent();

	_mesh = new Mesh(_vertices, _indices);
}

TerrainEditor::~TerrainEditor()
{
	delete _mesh;
	delete _worldBuffer;
	delete _material;
}

void TerrainEditor::Update()
{
}

void TerrainEditor::Render()
{
	_worldBuffer->SetData(_world);
	_worldBuffer->SetVSBuffer(0);

	_mesh->SetMesh();
	_material->SetMaterial();

	DC->DrawIndexed(_indices.size(), 0, 0);

	_material->PostRender();
}

void TerrainEditor::Debug()
{
}

bool TerrainEditor::Picking(OUT Vector3* position)
{
	Ray ray = Camera::GetInstance()->ScreenPointToRay(mousePos);

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

			if (TriangleTests::Intersects(ray.origion, ray.direction, pos[0], pos[1], pos[2], distance))
			{
				*position = ray.origion + ray.direction * distance;
				return true;
			}

			if (TriangleTests::Intersects(ray.origion, ray.direction, pos[3], pos[1], pos[2], distance))
			{
				*position = ray.origion + ray.direction * distance;
				return true;
			}
		}
	}

	return false;
}

void TerrainEditor::CreateMesh()
{
	//Vertex
	for (float z = 0; z < _height; z++)
	{
		for (float x = 0; x < _width; x++)
		{
			VertexType vertex;
			vertex.pos = Vector3(x, 0, z);

			vertex.uv.x = x / (_width - 1);
			vertex.uv.y = 1 - z / (_height - 1);

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

void TerrainEditor::CreateNormal()
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

void TerrainEditor::CreateTangent()
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
