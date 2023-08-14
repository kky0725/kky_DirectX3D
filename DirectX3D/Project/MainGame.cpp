#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	Initialize();

	scene = new TutorialScene();
}

MainGame::~MainGame()
{
	delete scene;

	Release();
}

void MainGame::Update()
{
	scene->Update();
}

void MainGame::Render()
{
	scene->PreRender();
	scene->Render();
	scene->PostRender();
}

void MainGame::Initialize()
{
}

void MainGame::Release()
{
}

