#pragma once
class Cube : public Transform
{
public:
	Cube(Vector4 color);
	virtual ~Cube();

	virtual void Update();
	void Render();
	
	void CreateMesh(Vector4 color);
	void SetPivot(Vector3 pos) { _pivot = pos; }

private:
	MatrixBuffer* _worldBuffer;

	vector<VertexColor>	_vertices;
	vector<UINT>		_indices;

	Material* _material;
	Mesh* _mesh;

	static int _count;
};