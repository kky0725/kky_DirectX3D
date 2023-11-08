#include "Framework.h"
#include "LightScene.h"

LightScene::LightScene()
{
	_floor = new Quad();
	_floor->SetLabel("Floor");
	_floor->_rotation.x = XM_PIDIV2;
	_floor->_translation.y = 1.0f;
	_floor->_scale *= 100.0f;
	_floor->GetMaterial()->SetShader(L"09Light");

	_groot = new Groot();
	_groot->GetReader()->SetShader(L"09Light");
	_bunny = new Model("StanfordBunny");
	_bunny->SetLabel("bunny");
	_bunny->_scale *= 0.05f;
	_bunny->_translation = { -30, 12, 0 };
	_bunny->GetReader()->SetShader(L"09Light");

	_sphere = new Sphere();
	_sphere->_scale *= 5.0f;
	_sphere->_translation = { 30, 20, 0 };
	_sphere->GetMaterial()->SetDiffuseMap(L"LandScape/FieldStone_DM.tga");
	_sphere->GetMaterial()->SetSpecularMap(L"LandScape/FieldStone_SM.tga");
	_sphere->GetMaterial()->SetNormalMap(L"LandScape/FieldStone_NM.tga");
	_sphere->GetMaterial()->SetShader(L"09Light");

}

LightScene::~LightScene()
{
	delete _floor;
	delete _bunny;
	delete _groot;
	delete _sphere;
}

void LightScene::Update()
{
	 _floor->Update();
	 _bunny->Update();
	 _groot->Update();
	_sphere->Update();
}

void LightScene::PreRender()
{
}

void LightScene::Render()
{
	 _floor->Render();
	 _bunny->Render();
	 _groot->Render();
	_sphere->Render();
}

void LightScene::PostRender()
{
	 _floor->Debug();
	 _bunny->GetReader()->Debug();
	 _groot->Debug();
	_sphere->GetMaterial()->Debug();
}