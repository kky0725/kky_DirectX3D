#pragma once
class Terrain : public Transform
{
	typedef VertexTextureNormalTangent VertexType;
public:
	Terrain(wstring diffuseFile, wstring heightFile);
	~Terrain();

	void Render();

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

	UINT _width	= 10;
	UINT _height= 10;

	Texture* _heightMap;

	const float MAP_HEIGHT = 20.0f;
};