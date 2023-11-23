#include "Framework.h"
#include "Reflection.h"

UINT Reflection::_index = 0;

Reflection::Reflection(Transform* target)
	:_target(target)
{
	_renderTarget = new RenderTarget(1280, 720);//크기는 여유있게, 비율은 맞추기
	_depthStencil = new DepthStencil(1280, 720);

	_camera = new Camera();

	// Debug()

	_quad = new Quad(Vector2(200, 200));
	//_quad->_translation = {150, 600, 0 };
	_quad->_translation = { 100, 100, 100 };

	Texture* texture = Texture::Get(L"Reflection" + to_wstring(_index++), _renderTarget->GetSRV());

	_quad->GetMaterial()->SetDiffuseMap(texture);
	_quad->Update();
}

Reflection::~Reflection()
{
	delete _renderTarget;
	delete _depthStencil;
	delete _camera;
	delete _quad;
}

void Reflection::Update()
{
	Vector3 pos = CAMERA->_translation;
	Vector3 rot = CAMERA->_rotation;

	pos.y = _target->GetGlobalPosition().y * 2.0f - pos.y;
	rot.x *= -1.0f;
	_camera->_translation = pos;
	_camera->_rotation = rot;

	_camera->Update();
}

void Reflection::SetPreRender()
{
	_renderTarget->Set(_depthStencil);

	_camera->SetView(); // slot 1 중복
}

void Reflection::SetRender()
{
	_camera->GetViewBuffer()->SetVSBuffer(10);
	DC->PSSetShaderResources(10, 1, &_renderTarget->GetSRV());
}

void Reflection::PostRender()
{
	_quad->Render();
}
