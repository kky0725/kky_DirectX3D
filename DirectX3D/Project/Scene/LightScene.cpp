#include "Framework.h"
#include "LightScene.h"

LightScene::LightScene()
{
	CreateObject();

	_renderTarget = new RenderTarget();
	_depthStencil = new DepthStencil();

	Texture* texture = Texture::Get(L"RenderTarget", _renderTarget->GetSRV());

	_floor->GetMaterial()->SetDiffuseMap(texture);
	_floor2->GetMaterial()->SetDiffuseMap(texture);

	_buffer = new FloatValueBuffer();
}

LightScene::~LightScene()
{
	delete _floor;
	delete _floor2;
	delete _bunny;
	delete _groot;
	delete _sphere;

	delete _renderTarget;
	delete _depthStencil;

	delete _buffer;
}

void LightScene::Update()
{
	 _floor->Update();
	 _floor2->Update();
	 _bunny->Update();
	 _groot->Update();
	_sphere->Update();
}

void LightScene::PreRender()
{
	_renderTarget->Set(_depthStencil, Vector4(1, 1, 0, 1));

	_bunny->Render();
	_groot->Render();
	_sphere->Render();
}

void LightScene::Render()
{
}

void LightScene::PostRender()
{
	_buffer->SetPSBuffer(10);
	
	const char* list[] = { "Mosaic", "Blur", "RadialBlur" };

	ImGui::Combo("Type", (int*)&_buffer->data.value[0], list, 3);

	ImGui::SliderFloat("Scale1", &_buffer->data.value[1], 1, 100);
	ImGui::SliderFloat("Scale2", &_buffer->data.value[2], 1, 640);
	ImGui::SliderFloat("Scale3", &_buffer->data.value[3], 1, 360);

	 _floor->Render();
	 _floor2->Render();
	// _floor->Debug();
	// _bunny->GetReader()->Debug();
	// _groot->Debug();
	//_sphere->GetMaterial()->Debug();
}

void LightScene::CreateObject()
{
	_floor = new Quad();
	_floor->SetLabel("Floor");
	//_floor->_rotation.x = XM_PIDIV2;
	//_floor->_translation.y = 1.0f;
	//_floor->_scale *= 100.0f;
	_floor->_scale.x = WIN_WIDTH  * 0.5f;
	_floor->_scale.y = WIN_HEIGHT * 0.5f;

	_floor->_translation.x = WIN_WIDTH * 0.25f;
	_floor->_translation.y = WIN_HEIGHT * 0.25f;

	//_floor->GetMaterial()->SetShader(L"09Light");
	_floor->GetMaterial()->SetShader(L"11PostEffect");

	_floor2 = new Quad();
	_floor2->SetLabel("Floor");
	_floor2->_scale.x = WIN_WIDTH * 0.5f;
	_floor2->_scale.y = WIN_HEIGHT * 0.5f;

	_floor2->_translation.x = WIN_WIDTH * 0.75f;
	_floor2->_translation.y = WIN_HEIGHT * 0.75f;

	_floor2->GetMaterial()->SetShader(L"10GrayScale");

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
