#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
	:Scene()
{
	_groot = new Groot();
	_terrain = new Terrain(L"Landscape/Dirt.png", L"HeightMap/HeightMap.png");
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

