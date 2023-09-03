#pragma once
class Sphere : public Transform
{
public:
	Sphere(Vector4 color, float radius);
	virtual ~Sphere();

	virtual void Update();
	void Render();

	void CreateMesh(Vector4 color);
	void CreateNormal();

private:
	MatrixBuffer* _worldBuffer;

	vector<VertexColorNormal>	_vertices;
	vector<UINT>				_indices;

	Material* _material;
	Mesh* _mesh;

	UINT _latitudes = 25;//위도의 수
	UINT _longitudes = 25;//경도의 수
	float _radius;
};