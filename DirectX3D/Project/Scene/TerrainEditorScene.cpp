#include "Framework.h"
#include "TerrainEditorScene.h"

TerrainEditorScene::TerrainEditorScene()
{
	_terrainEidtor = new TerrainEditor();
	_terrainEidtor->Getmaterial()->SetDiffuseMap(L"Landscape/fieldstone_DM.tga");
	_terrainEidtor->Getmaterial()->SetSpecularMap(L"Landscape/fieldstone_SM.tga");
	_terrainEidtor->Getmaterial()->SetNormalMap(L"Landscape/fieldstone_NM.tga");
}

TerrainEditorScene::~TerrainEditorScene()
{
	delete _terrainEidtor;
}

void TerrainEditorScene::Update()
{
	_terrainEidtor->Update();

	if (KEY_DOWN(VK_LBUTTON))
		_terrainEidtor->Picking(&_pickedPos);
}

void TerrainEditorScene::PreRender()
{
}

void TerrainEditorScene::Render()
{	
	//RS->ChangeState(D3D11_FILL_WIREFRAME);
	_terrainEidtor->Render();
	//RS->ChangeState(D3D11_FILL_SOLID);
}

void TerrainEditorScene::PostRender()
{
	_terrainEidtor->Debug();
	_terrainEidtor->Getmaterial()->SeletMap();

	ImGui::Text("PickedPos : %.1f, %.1f, %.1f", _pickedPos.x, _pickedPos.y, _pickedPos.z);
}
