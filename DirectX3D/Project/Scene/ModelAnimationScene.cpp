#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
	:Scene()
{
	_groot = new Groot();
	_terrain = new Terrain(L"Landscape/Dirt.png", L"HeightMap/HeightMap.png");
	_terrain->_scale = Vector3(2.0f, 2.0f, 2.0f);

	Camera::GetInstance()->SetTarget(_groot);
}

ModelAnimationScene::~ModelAnimationScene()
{
	delete _groot;
	delete _terrain;
}

void ModelAnimationScene::Update()
{
	_groot->Update();
	_terrain->Update();

	_groot->_translation.y = _terrain->GetHeight(_groot->GetGlobalPosition());
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
	_groot->Render();
	_terrain->Render();
}

void ModelAnimationScene::PostRender()
{
	_groot->Debug();
}

