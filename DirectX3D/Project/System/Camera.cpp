#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	_viewBuffer = new MatrixBuffer();

	_transform = new Transform();

	//_transform->_translation = { 120.0f, 100.0f, -20.0f };
	_transform->_translation = { 0.0f, 0.0f, -20.0f };
	_transform->_rotation.x = 0.65f;
}

Camera::~Camera()
{
	delete _transform;

	delete _viewBuffer;
}

void Camera::Update()
{
	FreeMode();
}

void Camera::PostRender()
{
	ImGui::Text("Camera Pos x : %.2f, y : %.2f, z : %.2f", _transform->_translation.x, _transform->_translation.y, _transform->_translation.z);
	ImGui::Text("Camera Rot x : %.2f, y : %.2f, z : %.2f", _transform->_rotation.x, _transform->_rotation.y, _transform->_rotation.z);
}

void Camera::FreeMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS(VK_LSHIFT))
			_moveSpeed = 50.0f;
		else
			_moveSpeed = 20.0f;

		if (KEY_PRESS('A'))
			_transform->_translation += _transform->Left() * _moveSpeed * Time::Delta();

		if (KEY_PRESS('D'))
			_transform->_translation += _transform->Right() * _moveSpeed * Time::Delta();

		if (KEY_PRESS('S'))
			_transform->_translation += _transform->Backward() * _moveSpeed * Time::Delta();

		if (KEY_PRESS('W'))
			_transform->_translation += _transform->Forward() * _moveSpeed * Time::Delta();

		if (KEY_PRESS('Q'))
			_transform->_translation += _transform->Up() * _moveSpeed * Time::Delta();

		if (KEY_PRESS('E'))
			_transform->_translation += _transform->Down() * _moveSpeed * Time::Delta();
	
		Vector3 dir = mousePos - _oldPos;

		_transform->_rotation.y += dir.x * _rotSpeed * Time::Delta();
		_transform->_rotation.x += dir.y * _rotSpeed * Time::Delta();
	}

	_oldPos = mousePos;

	SetView();
}

void Camera::TargetMode()
{
}

void Camera::SetView()
{
	_transform->Update();

	XMVECTOR eyePos   = _transform->_translation;
	XMVECTOR focusPos = _transform->_translation + _transform->Forward();
	XMVECTOR upVector = _transform->Up();

	_viewMatrix = XMMatrixLookAtLH(eyePos, focusPos, upVector);

	_viewBuffer->SetData(_viewMatrix);
	_viewBuffer->SetVSBuffer(1);
}