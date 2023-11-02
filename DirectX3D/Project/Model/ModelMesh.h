#pragma once
class ModelMesh
{
	friend class ModelReader;
public:
	ModelMesh();
	~ModelMesh();

	//Mesh* GetMesh() { return _mesh; }
	//Material* GetMaterial() { return _material; }
	//UINT GetIndicesSize() { return _indices.size(); }

	void CreateMesh();
	void Render();

	void RenderInstanced(UINT instanceCount);

private:
	string _name;

	Material* _material;

	Mesh* _mesh;

	vector<ModelVertex> _vertices;
	vector<UINT>		_indices;
};