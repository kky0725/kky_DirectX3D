#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	_textureCube = new TextureCube();
	_textureCube->SetLabel("Cube");
	CAMERA->_translation = { 0, 3, -5 };

	_cube = new Cube({ 1.0f, 0.0f, 0.0f, 1.0f });
	_cube->_translation.x = 2;

	_sphere = new Sphere();
	_sphere->_translation.x = -2;

	_sphere->GetMaterial()->SetDiffuseMap(L"Landscape/Fieldstone_DM.tga");
	_sphere->GetMaterial()->SetSpecularMap(L"Landscape/Fieldstone_SM.tga");

}

TextureScene::~TextureScene()
{
	delete _textureCube;
	delete _cube;
	delete _sphere;
}

void TextureScene::Update()
{
	_cube->_rotation.x += Time::GetInstance()->Delta();
	_textureCube->_rotation.x += Time::GetInstance()->Delta();
	_sphere->_rotation.y += Time::GetInstance()->Delta();

	_textureCube->Update();
	_cube->Update();

	_sphere->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	_textureCube->Render();
	_cube->Render();

	//RS->ChangeState(D3D11_FILL_WIREFRAME);
	_sphere->Render();
	//RS->ChangeState(D3D11_FILL_SOLID);
}

void TextureScene::PostRender()
{
	_textureCube->Debug();

	_sphere->GetMaterial()->PostRender();
}

