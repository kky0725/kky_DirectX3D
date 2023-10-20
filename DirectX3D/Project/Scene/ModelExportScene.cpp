#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Groot";

	_exporter = new ModelExporter(name);
	_exporter->ExportModel();
	_exporter->ExportClip("Sad Idle");
	_exporter->ExportClip("Running");
	_exporter->ExportClip("Mutant Swiping");

	//_model = new Model(name);
}

ModelExportScene::~ModelExportScene()
{
	delete _exporter;
	//delete _model;
}

void ModelExportScene::Update()
{
	//_model->Update();
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
	//_model->Render();
}

void ModelExportScene::PostRender()
{
	//_model->GetReader()->Debug();
}
