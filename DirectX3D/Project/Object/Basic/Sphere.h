#pragma once
class Sphere : public Transform
{
	typedef VertexTextureNormalTangent VertexType;
public:
	Sphere(float radius = 1.0f, UINT latitudes = 10, UINT longitudes = 20);
	virtual ~Sphere();

	virtual void Update();
	void Render();

	Material* GetMaterial() { return _material; }

private:
	void CreateMesh();
	void CreateTangent();

	MatrixBuffer* _worldBuffer;

	vector<VertexType>	_vertices;
	vector<UINT>		_indices;

	Material* _material;
	Mesh* _mesh;

	UINT  _latitudes;//������ ��//stack
	UINT _longitudes;//�浵�� ��//slice
	float _radius;
};