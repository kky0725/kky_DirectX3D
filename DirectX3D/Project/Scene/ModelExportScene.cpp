#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Knight D Pelegrini";

	//_exporter = new ModelExporter(name);
	//_exporter->ExportModel();
	//_exporter->ExportClip("Hip Hop Dancing");
	//_exporter->ExportClip("Running");
	//_exporter->ExportClip("Idle");

	//_model = new Model(name);
	_modelAnimator = new ModelAnimator(name);
	_modelAnimator->ReadClip("Hip Hop Dancing");
	_modelAnimator->ReadClip("Running");
	_modelAnimator->ReadClip("Idle");
	_modelAnimator->CreateTexture();
}

ModelExportScene::~ModelExportScene()
{
	//delete _exporter;
	//delete _model;
	delete _modelAnimator;
}

void ModelExportScene::Update()
{
	//_model->Update();
	_modelAnimator->Update();

	if (KEY_DOWN('1'))
		_modelAnimator->PlayClip(0, speed, takeTime);

	if (KEY_DOWN('2'))
		_modelAnimator->PlayClip(1, speed, takeTime);

	if (KEY_DOWN('3'))
		_modelAnimator->PlayClip(2, speed, takeTime);
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
	_modelAnimator->Debug();

	ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
	ImGui::SliderFloat("TakeTime", &takeTime, 0.0f, 1.0f);
}
