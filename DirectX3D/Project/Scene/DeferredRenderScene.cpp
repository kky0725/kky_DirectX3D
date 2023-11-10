#include "Framework.h"
#include "DeferredRenderScene.h"

DeferredRenderScene::DeferredRenderScene()
{
	CreateObject();

	_gBuffer = new GeomtryBuffer();

	_material = new Material(L"12DeferredRender");

	vector<UINT> vertices = { 0, 1, 2, 3 };

	_vertexBuffer = new VertexBuffer(vertices);
}

DeferredRenderScene::~DeferredRenderScene()
{
	delete _gBuffer;

	delete _floor;
	delete _bunny;
	delete _groot;
	delete _sphere;

	delete _material;
	delete _vertexBuffer;
}

void DeferredRenderScene::Update()
{
	_floor->Update();
	_bunny->Update();
	_groot->Update();
	_sphere->Update();
}

void DeferredRenderScene::PreRender()
{
	_gBuffer->SetMultiRenderTarget();

	_floor->Render();
	_bunny->Render();
	_groot->Render();
	_sphere->Render();
}

void DeferredRenderScene::Render()
{
	_vertexBuffer->IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	_gBuffer->SetSRVs();
	_material->SetMaterial();
	
	//	 Camera::GetInstance()->GetViewBuffer()->SetPSBuffer(1);
	//Environment::GetInstance()->GetPersBuffer()->SetPSBuffer(2);

	DC->Draw(4, 0);
}

void DeferredRenderScene::PostRender()
{
	_gBuffer->PostRender();
}

void DeferredRenderScene::CreateObject()
{
	_floor = new Quad();
	_floor->SetLabel("Floor");
	_floor->_rotation.x = XM_PIDIV2;
	_floor->_translation.y = 1.0f;
	_floor->_scale *= 100.0f;

	_floor->GetMaterial()->SetShader(L"12GeometryBuffer");

	_groot = new Groot();
	_groot->GetReader()->SetShader(L"12GeometryBuffer");
	_bunny = new Model("StanfordBunny");
	_bunny->SetLabel("bunny");
	_bunny->_scale *= 0.05f;
	_bunny->_translation = { -30, 12, 0 };
	_bunny->GetReader()->SetShader(L"12GeometryBuffer");

	_sphere = new Sphere();
	_sphere->_scale *= 5.0f;
	_sphere->_translation = { 30, 20, 0 };
	_sphere->GetMaterial()->SetDiffuseMap(L"LandScape/FieldStone_DM.tga");
	_sphere->GetMaterial()->SetSpecularMap(L"LandScape/FieldStone_SM.tga");
	_sphere->GetMaterial()->SetNormalMap(L"LandScape/FieldStone_NM.tga");
	_sphere->GetMaterial()->SetShader(L"12GeometryBuffer");
}


