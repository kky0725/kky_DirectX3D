#pragma once
class ModelReader
{
public:
	ModelReader(string name);
	~ModelReader();

	void SetShader(wstring file);

	void Render();

	void Debug();

private:
	void ReadMaterial();
	void ReadMesh();

private:
	string _name;

	vector<Material*> _materials;
	vector<ModelMesh*> _meshes;

	vector<NodeData> _nodes;
	vector<BoneData> _bones;

	map<string, UINT> _boneMap;
};