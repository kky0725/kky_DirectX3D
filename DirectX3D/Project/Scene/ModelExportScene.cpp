#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	_exporter = new ModelExporter("Knight D Pelegrini");
	_exporter->ExportModel();
	_reader = new ModelReader("Knight D Pelegrini");

	_model = new Model("Knight D Pelegrini");
}

ModelExportScene::~ModelExportScene()
{
	delete _exporter;
	delete _reader;
	delete _model;
}

void ModelExportScene::Update()
{
	_model->Update();
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
	_model->Render();
}

void ModelExportScene::PostRender()
{
}
