#pragma once
class ModelReader
{
	friend class ModelAnimator;
public:
	ModelReader(string name);
	~ModelReader();

	void SetShader(wstring file);

	void Render();

	void Debug();

	bool HasBone(string boneName) { return _boneMap.count(boneName) > 0; }

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