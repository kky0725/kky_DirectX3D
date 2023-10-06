#pragma once
class ModelReader
{
public:
	ModelReader(string name);
	~ModelReader();

	void SetShader(wstring file);

private:
	void ReadMaterial();
	void ReadMesh();

private:
	string _name;

	vector<Material*> _materials;
	vector<ModelMesh*> _meshes;
};