#include "Framework.h"
#include "TerrainScene.h"

#include "../Object/Robot.h"

TerrainScene::TerrainScene()
{
	_terrain = new Terrain(L"Landscape/Dirt.png", L"HeightMap/HeightMap.png");

	_robot = new Robot();
}

TerrainScene::~TerrainScene()
{
	delete _robot;
	delete _terrain;
}

void TerrainScene::Update()
{
	_terrain->Update();
	_robot->Update();
	

	if (KEY_DOWN(VK_LBUTTON))
	{
		_terrain->Picking(&_pickedPos);
		_robot->SetPosition(_pickedPos + Vector3(0.0f, 4.0f, 0.0f));
	}
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	_terrain->Render();
	_robot->Render();
}

void TerrainScene::PostRender()
{

}