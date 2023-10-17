#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Knight D Pelegrini";

	_exporter = new ModelExporter(name);
	_exporter->ExportModel();
	_exporter->ExportClip("Hip Hop Dancing");

	//_model = new Model(name);
	_modelAnimator = new ModelAnimator(name);
	_modelAnimator->ReadClip("Hip Hop Dancing");
	_modelAnimator->CreateTexture();
}

ModelExportScene::~ModelExportScene()
{
	delete _exporter;
	//delete _model;
	delete _modelAnimator;
}

void ModelExportScene::Update()
{
	//_model->Update();
	_modelAnimator->Update();
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
	//_model->Render();
	_modelAnimator->Render();
}

void ModelExportScene::PostRender()
{
	//_model->GetReader()->Debug();
	//_modelAnimator->Debug();
}
