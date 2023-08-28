#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	_imageCube = new ImageCube();
}

TestScene::~TestScene()
{
	delete _imageCube;
}

void TestScene::Update()
{
	_imageCube->Update();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	_imageCube->Render();
}

void TestScene::PostRender()
{

	_imageCube->Debug();
}

