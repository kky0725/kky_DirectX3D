#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	_textureCube = new TextureCube();
	_textureCube->SetLabel("Cube");
	CAMERA->_translation = { 0, 3, -5 };

	_cube = new Cube({ 1.0f, 0.0f, 0.0f, 1.0f });
	_cube->_translation.x = 2;

}

TextureScene::~TextureScene()
{
	delete _textureCube;
	delete _cube;
}

void TextureScene::Update()
{
	_cube->_rotation.x += Time::GetInstance()->Delta();
	_textureCube->_rotation.x += Time::GetInstance()->Delta();
	_textureCube->Update();
	_cube->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	_textureCube->Render();
	_cube->Render();
}

void TextureScene::PostRender()
{
	_textureCube->Debug();
}

