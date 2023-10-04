#pragma once
class ModelExporter
{
public:
	ModelExporter(string name);
	~ModelExporter();

	void ExportMaterial();

	wstring CreateTexture(string file);

private:
	string _name;

	Assimp::Importer* _importer;

	const aiScene* _scene;

	vector<Material*> _materials;
};