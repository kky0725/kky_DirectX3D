#pragma once
class ModelExporter
{
public:
	ModelExporter(string file);
	~ModelExporter();

	void ExportMaterial(string name);
	void ReadMaterial();

	wstring CreateTexture(string file);

private:
	string _name;

	Assimp::Importer* _importer;

	const aiScene* _scene;

	vector<Material*> _materials;
};