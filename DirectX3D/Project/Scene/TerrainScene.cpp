#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	_terrain = new Terrain(L"Landscape/Dirt.png", L"HeightMap/HeightMap.png");
}

TerrainScene::~TerrainScene()
{
	delete _terrain;
}

void TerrainScene::Update()
{
	_terrain->Update();
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	_terrain->Render();
}

void TerrainScene::PostRender()
{

}