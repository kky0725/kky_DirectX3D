#pragma once
class ModelMesh
{
	friend class ModelReader;
public:
	ModelMesh();
	~ModelMesh();

	Mesh* GetMesh() { return _meshes; }
	UINT GetIndicesSize() { return _indices.size(); }

private:
	string _name;

	UINT _materialIndex;

	//Material* _material;

	Mesh* _meshes;

	vector<ModelVertex> _vertices;
	vector<UINT>		_indices;
};