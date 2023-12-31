#pragma once
class Terrain : public Transform
{
	typedef VertexTextureNormalTangent VertexType;
public:
	Terrain(wstring diffuseFile, wstring heightFile);
	~Terrain();

	void Render();

	bool Picking(OUT Vector3* position);

	float GetHeight(Vector3 position);

	Vector2 GetSize() { return Vector2(_width, _height); }

private:
	void CreateMesh();
	void CreateNormal();
	void CreateTangent();

private:
	vector<VertexType>	_vertices;
	vector<UINT>		_indices;

	Material*	_material;
	Mesh*		_mesh;

	UINT _width	= 10;
	UINT _height= 10;

	Texture* _heightMap;

	const float MAP_HEIGHT = 20.0f;
};