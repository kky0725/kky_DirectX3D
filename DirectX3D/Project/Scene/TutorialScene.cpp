#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_cube = new Cube;
}

TutorialScene::~TutorialScene()
{
	delete _cube;
}

void TutorialScene::Update()
{
	_cube->Update();
}

void TutorialScene::PreRender()
{
}

void TutorialScene::Render()
{
	_cube->Render();
}

void TutorialScene::PostRender()
{
}
