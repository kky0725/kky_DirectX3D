#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	//_exporter = new ModelExporter("Y Bot");
	//_exporter->ExportModel();

	_model = new Model("Y Bot");
}

ModelExportScene::~ModelExportScene()
{
	//delete _exporter;
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
	_model->GetReader()->Debug();

}
