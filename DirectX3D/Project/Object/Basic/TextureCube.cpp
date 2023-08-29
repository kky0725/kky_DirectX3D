#include "Framework.h"
#include "TextureCube.h"

TextureCube::TextureCube()
{
	CreateQuads();
}

TextureCube::~TextureCube()
{
	for (Quad* quad : _quads)
		delete quad;

	_quads.clear();
}

void TextureCube::Update()
{
	for (Quad* quad : _quads)
		quad->Update();

	Transform::Update();
}

void TextureCube::Render()
{
	for (Quad* quad : _quads)
		quad->Render();
}

void TextureCube::CreateQuads()
{
	_quads.resize(6);

	_quads[LEFT] = new Quad();
	_quads[LEFT]->_translation.x = -0.5f;
	_quads[LEFT]->_rotation.y = +XM_PIDIV2;
	_quads[LEFT]->SetParent(this);

	_quads[RIGHT] = new Quad();
	_quads[RIGHT]->_translation.x = +0.5f;
	_quads[RIGHT]->_rotation.y = -XM_PIDIV2;
	_quads[RIGHT]->SetParent(this);

	_quads[BOTTOM] = new Quad();
	_quads[BOTTOM]->_translation.y = -0.5f;
	_quads[BOTTOM]->_rotation.x = -XM_PIDIV2;
	_quads[BOTTOM]->SetParent(this);

	_quads[TOP] = new Quad();
	_quads[TOP]->_translation.y = +0.5f;
	_quads[TOP]->_rotation.x = +XM_PIDIV2;
	_quads[TOP]->SetParent(this);

	_quads[FRONT] = new Quad();
	_quads[FRONT]->_translation.z = -0.5f;
	_quads[FRONT]->SetParent(this);

	_quads[BACK] = new Quad();
	_quads[BACK]->_translation.z = +0.5f;
	_quads[BACK]->_rotation.x = XM_PI;
	_quads[BACK]->SetParent(this);
}

