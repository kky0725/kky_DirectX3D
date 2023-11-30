#include "Framework.h"
#include "TerrainLODScene.h"

TerrainLODScene::TerrainLODScene()
{
	_terrain = new TerrainLOD(L"LandScape/Dirt2.png");
}

TerrainLODScene::~TerrainLODScene()
{
	delete _terrain;
}

void TerrainLODScene::Update()
{
	_terrain->Update();
}

void TerrainLODScene::PreRender()
{
}

void TerrainLODScene::Render()
{
	_terrain->Render();
}

void TerrainLODScene::PostRender()
{
	_terrain->Debug();
}
