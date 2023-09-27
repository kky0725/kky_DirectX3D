#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Knight D Pelegrini";

	_exporter = new ModelExporter("_ModelData/FBX/" + name + ".fbx");
	_exporter->ExportMaterial(name);
}

ModelExportScene::~ModelExportScene()
{
	delete _exporter;
}

void ModelExportScene::Update()
{
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
}

void ModelExportScene::PostRender()
{
}
