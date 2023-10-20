#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
	:Scene()
{
	_groot = new Groot();
}

ModelAnimationScene::~ModelAnimationScene()
{
	delete _groot;
}

void ModelAnimationScene::Update()
{
	_groot->Update();
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
	_groot->Render();
}

void ModelAnimationScene::PostRender()
{
	_groot->Debug();
}

