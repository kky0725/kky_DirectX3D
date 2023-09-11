#pragma once
class TerrainEditor : public Transform
{
	typedef VertexTextureNormalTangent VertexType;
public:
	TerrainEditor(UINT height = 100, UINT width = 100);
	virtual ~TerrainEditor();

	void Update();
	void Render();

	void Debug();

	Material* Getmaterial() { return _material; }

	bool Picking(OUT Vector3* position);

private:
	void CreateMesh();
	void CreateNormal();
	void CreateTangent();

private:
	vector<VertexType>	_vertices;
	vector<UINT>		_indices;

	Material*	_material;
	Mesh*		_mesh;

	MatrixBuffer* _worldBuffer;

	UINT _width;
	UINT _height;

	Texture* _heightMap;

	const float MAP_HEIGHT = 20.0f;
};

