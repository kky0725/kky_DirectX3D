#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	_textureCube = new TextureCube();
	_textureCube->SetLabel("Cube");
}

TextureScene::~TextureScene()
{
	delete _textureCube;
}

void TextureScene::Update()
{
	_textureCube->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	_textureCube->Render();
}

void TextureScene::PostRender()
{
	_textureCube->Debug();
}

