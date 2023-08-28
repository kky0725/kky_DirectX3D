#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	_quad = new Quad();
}

TextureScene::~TextureScene()
{
	delete _quad;
}

void TextureScene::Update()
{
	_quad->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	_quad->Render();
}

void TextureScene::PostRender()
{
}

