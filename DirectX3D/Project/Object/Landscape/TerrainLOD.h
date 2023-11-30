#pragma once
class TerrainLOD : public Transform
{
private:
	typedef VertexTexture VertexType;

public:
	TerrainLOD(wstring heightMap);
	~TerrainLOD();

	void Render();
	void Debug();

private:
	void CreateMesh();

private:
	UINT _width, _height;
	UINT _patchWidth, _patchHeight;

	UINT	_cellsPerPatch = 32;
	float	_cellSpacing = 5.0f;
	Vector2 _cellUV;

	Material*	_material;
	Mesh*		_mesh;

	vector<VertexType> _vertices;
	vector<UINT> _indices;

	Texture* _heightMap;

	FloatValueBuffer* _terrainBuffer;
	FloatValueBuffer* _heightBuffer;

	HullShader*		_hullShader;
	DomainShader*	_domainShader;
};