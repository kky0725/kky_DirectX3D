#pragma once
class ModelExporter
{
public:
	ModelExporter(string name);
	~ModelExporter();

	void ExportModel();

private:
	void ExportMaterial();
	void ExportMesh();

	wstring CreateTexture(string file);

	void ReadMesh(aiNode* node);
	void ReadNode(aiNode* node, int index, int parent);
	void ReadBone(aiMesh* mesh, vector<VertexWeight>& vertexWeights);
	
	void WriteMesh();

private:
	string _name;

	Assimp::Importer* _importer;

	const aiScene* _scene;

	vector<MeshData*> _meshes;

	vector<string> _materialNames;

	vector<NodeData*> _nodes;
	vector<BoneData*> _bones;

	map<string, UINT> _boneMap;

	UINT _boneCount = 0;
};