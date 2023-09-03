#include "Framework.h"
#include "TestScene.h"

#include "Object/Robot.h"

TestScene::TestScene()
{
	_sphere = new Sphere(Vector4(0.2f, 0.2f, 1.0f, 1.0f), 5.0f);
}

TestScene::~TestScene()
{
	delete _sphere;
}

void TestScene::Update()
{
	_sphere->Update();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	_sphere->Render();
}

void TestScene::PostRender()
{

}

