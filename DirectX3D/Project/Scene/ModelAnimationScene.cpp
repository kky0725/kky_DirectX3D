#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
	:Scene()
{
	_groot = new Groot();
	_terrain = new Terrain(L"Landscape/Dirt.png", L"HeightMap/HeightMap.png");
	_terrain->_scale = Vector3(2.0f, 2.0f, 2.0f);

	//Camera::GetInstance()->SetTarget(_groot);

	_crossHair = new Quad();
	_crossHair->GetMaterial()->SetDiffuseMap(L"UI/CrossHair.png");
	_crossHair->GetMaterial()->SetShader(L"Texture");
	_crossHair->_scale = { 200, 200, 1 };

	_sky = new Sky();
}

ModelAnimationScene::~ModelAnimationScene()
{
	delete _groot;
	delete _terrain;
	delete _crossHair;
	delete _sky;
}

void ModelAnimationScene::Update()
{
	_groot->Update();
	_terrain->Update();
	_crossHair->Update();

	_crossHair->_translation.x = mousePos.x;
	_crossHair->_translation.y = WIN_HEIGHT - mousePos.y;

	_groot->_translation.y = _terrain->GetHeight(_groot->GetGlobalPosition());
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
	_sky->Render();
	_groot->Render();
	_terrain->Render();
}

void ModelAnimationScene::PostRender()
{
	_groot->PostRender();

	//StateManager::GetInstance()->AlphaBegin();
	_crossHair->Render();
	//StateManager::GetInstance()->AlphaEnd();

	_sky->PostRender();
}

