#include "Framework.h"
#include "WaterScene.h"

WaterScene::WaterScene()
{
	CreateObject();

	//_reflection = new Reflection(_floor);
	//_refraction = new Refraction(L"LandScape/Wave.dds");

	_sky = new SkyBox(L"LandScape/Snow_ENV.dds");

	//_floor->GetMaterial()->SetShader(L"19Reflection");
	_floor->GetMaterial()->SetShader(L"20Refraction");

	_water = new Water(L"Landscape/Wave.dds");
}

WaterScene::~WaterScene()
{
	delete _floor;
	delete _bunny;
	delete _groot;
	delete _sphere;

	//delete _reflection;
	//delete _refraction;

	delete _water;
}

void WaterScene::Update()
{
	//_reflection->Update();
	//_refraction->Update();
	_water->Update();

	_floor->Update();
	_bunny->Update();
	_groot->Update();
	_sphere->Update();
}

void WaterScene::PreRender()
{
	//_reflection->SetPreRender();
	//_refraction->SetPreRender();
	_water->SetReflection();

	_sky->Render();

	_bunny->Render();
	_groot->Render();
	_sphere->Render();

	_water->SetRefraction();

	_sky->Render();

	_bunny->Render();
	_groot->Render();
	_sphere->Render();
}

void WaterScene::Render()
{
	_sky->Render();

	//_reflection->SetRender();
	//_refraction->SetRender();
	_water->Render();

	//_floor->Render();
	_bunny->Render();
	_groot->Render();
	_sphere->Render();
}

void WaterScene::PostRender()
{
	//_reflection->PostRender();
	//_refraction->PostRender();
	//_refraction->DeBug();
	_water->Debug();
	_floor->Debug();
}

void WaterScene::CreateObject()
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


