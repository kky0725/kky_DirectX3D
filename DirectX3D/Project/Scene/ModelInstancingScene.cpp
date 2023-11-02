#include "Framework.h"
#include "ModelInstancingScene.h"

ModelInstancingScene::ModelInstancingScene()
{
	_model = new ModelAnimatorInstancing("Groot");
	_model->ReadClip("Sad Idle");
	_model->ReadClip("Running");
	_model->ReadClip("Mutant Swiping");

	_model->GetReader()->GetMaterial()[0]->SetDiffuseMap(L"Model/Groot/groot_diffuse.png");
	_model->GetReader()->GetMaterial()[0]->SetNormalMap(L"Model/Groot/groot_normal_map.png");

	for (float z = 0; z < 10; z++)
	{
		for (float x = 0; x < 10; x++)
		{
			Transform* transform = _model->Add();
			transform->_translation = { x * 10, 0, z * 10 };
			transform->_scale *= 0.01f;
		}
	}
}

ModelInstancingScene::~ModelInstancingScene()
{
}

void ModelInstancingScene::Update()
{
	_model->Update();
}

void ModelInstancingScene::PreRender()
{
}

void ModelInstancingScene::Render()
{
	_model->Render();
}

void ModelInstancingScene::PostRender()
{
	ImGui::SliderInt("InstanceIndex", &_instanceIndex, 0, 99);
	ImGui::SliderInt("ClipIndex", &_clip, 0, 2);

	if (ImGui::Button("Play"))
		_model->PlayClip(_instanceIndex, _clip);

	_model->Debug();
}


