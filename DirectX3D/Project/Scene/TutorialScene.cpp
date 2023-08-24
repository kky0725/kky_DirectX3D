#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_cube1 = new Cube({1.0f, 0.0f, 0.0f, 1.0f});
	_cube2 = new Cube({0.0f, 1.0f, 0.0f, 1.0f});

	//_cube2->_translation.x = 3;

	_cube2->SetParent(_cube1);
}

TutorialScene::~TutorialScene()
{
	delete _cube1;
	delete _cube2;
}

void TutorialScene::Update()
{
	_cube1->Update();
	_cube2->Update();

	if (KEY_PRESS(VK_LEFT))
		_cube1->_translation += _cube1->Left() * Time::Delta();

	if (KEY_PRESS(VK_RIGHT))
		_cube1->_translation += _cube1->Right() * Time::Delta();

	if (KEY_PRESS(VK_UP))
		_cube1->_translation += _cube1->Up() * Time::Delta();

	if (KEY_PRESS(VK_DOWN))
		_cube1->_translation += _cube1->Down() * Time::Delta();

	if (KEY_PRESS('Q'))
		_cube1->_rotation.z += Time::Delta();

	if (KEY_PRESS('E'))
		_cube1->_rotation.z -= Time::Delta();
	//_cube1->_rotation.y += 0.0001f;
}

void TutorialScene::PreRender()
{
}

void TutorialScene::Render()
{
	_cube1->Render();
	_cube2->Render();
}

void TutorialScene::PostRender()
{
	_cube1->Debug();
	_cube2->Debug();
}
