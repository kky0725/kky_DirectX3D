#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	_exporter = new ModelExporter("Knight D Pelegrini");
	_exporter->ExportModel();
	_reader = new ModelReader("Knight D Pelegrini");
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
