#pragma once
class TerrainScene : public Scene
{
public:
	TerrainScene();
	~TerrainScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void CreateMesh();

private:
	vector<VertexTexture>	_vertices;
	vector<UINT>			_indices;

	Material*	_material;
	Mesh*		_mesh;

	MatrixBuffer* _worldBuffer;

	UINT _width	= 10;
	UINT _height= 10;

	Texture* _heightMap;

	const float MAP_HEIGHT = 20.0f;
};