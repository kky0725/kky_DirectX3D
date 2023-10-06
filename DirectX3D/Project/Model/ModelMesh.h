#pragma once
class ModelMesh
{
	friend class ModelReader;
public:
	ModelMesh();
	~ModelMesh();

private:
	string _name;

	UINT _materialIndex;

	Material* _material;

	Mesh* _mesh;

	vector<ModelVertex> _vertices;
	vector<UINT>		_indices;
};