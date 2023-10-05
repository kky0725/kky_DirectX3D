#pragma once
class ModelExporter
{
public:
	ModelExporter(string name);
	~ModelExporter();

	void ExportModel();

	void ExportMaterial();
	void ExportMesh();

	wstring CreateTexture(string file);

	void ReadMesh(aiNode* node);
	void WriteMesh();

private:
	string _name;

	Assimp::Importer* _importer;

	const aiScene* _scene;

	vector<MeshData*> _meshes;
};