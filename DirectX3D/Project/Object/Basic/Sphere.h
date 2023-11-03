#pragma once
class Sphere : public Transform
{
	typedef VertexTextureNormalTangent VertexType;
public:
	Sphere(float radius = 1.0f, UINT sliceCount = 10, UINT stackCount = 20);
	virtual ~Sphere();

	virtual void Update();
	void Render();

	Material* GetMaterial() { return _material; }

private:
	void CreateMesh();
	void CreateTangent();

	vector<VertexType>	_vertices;
	vector<UINT>		_indices;

	Material* _material;
	Mesh* _mesh;

	UINT _sliceCount;
	UINT _stackCount;
	float _radius;
};