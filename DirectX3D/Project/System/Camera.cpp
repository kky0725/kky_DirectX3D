#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	_viewBuffer = new ViewBuffer();

	_transform = new Transform();

	_transform->_translation = { 60.0f, 100.0f, -80.0f };
	//_transform->_translation = { 0.0f, 0.0f, -20.0f };
	_transform->_rotation.x = 0.65f;

	//Load();
}

Camera::~Camera()
{
	Save();

	delete _transform;

	delete _viewBuffer;
}

void Camera::Update()
{
	if(!_target)
		FreeMode();
	else
		TargetMode();
}

void Camera::Debug()
{
	if (ImGui::TreeNode("Camera Option"))
	{
		ImGui::Text("Camera Pos x : %.2f, y : %.2f, z : %.2f", _transform->_translation.x, _transform->_translation.y, _transform->_translation.z);
		ImGui::Text("Camera Rot x : %.2f, y : %.2f, z : %.2f", _transform->_rotation.x, _transform->_rotation.y, _transform->_rotation.z);

		ImGui::SliderFloat("Camera MoveDamping", &_moveDamping, 0.0f, 30.0f);
		ImGui::SliderFloat("Camera RotDamping", &_rotDamping, 0.0f, 30.0f);
		ImGui::SliderFloat("Camera RotY", &_rotY, 0.0f, XM_2PI);

		ImGui::TreePop();
	}
}

Ray Camera::ScreenPointToRay(Vector3 screenPos)
{
	Ray ray;
	ray.origion = _transform->_translation;

	//////InvViewport/////// LeftTop이 0,0이라는 가정

	Vector3 point;

	point.x = +(2.0f * screenPos.x) / WIN_WIDTH - 1.0f;
	point.y = -(2.0f * screenPos.y) / WIN_HEIGHT + 1.0f;
	point.z = 1.0f;//FarZ

	///////Invprojection///////

	Matrix projection = Environment::GetInstance()->GetProjMatirx();

	XMFLOAT4X4 proj;
	XMStoreFloat4x4(&proj, projection);

	point.x /= proj._11;
	point.y /= proj._22;

	////InvView/////

	Matrix invView = _transform->GetWorld();

	ray.direction = point * invView;
	ray.direction.Normalize();

	return ray;
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

		if (abs(dir.x) > 15.0f || abs(dir.y) > 15.0f)
			dir = Vector3(0.0f, 0.0f, 0.0f);

		_transform->_rotation.y += dir.x * _rotSpeed * Time::Delta();
		_transform->_rotation.x += dir.y * _rotSpeed * Time::Delta();
	}

	_oldPos = mousePos;

	_viewMatrix = XMMatrixInverse(nullptr, _transform->GetWorld());

	SetView();
}

void Camera::TargetMode()
{
	//위치랑 회전을 따라감
	//_destination = _target->_translation - _target->Backward() * _distance + V_UP * _height;
	//
	//_transform->_translation = _destination;

	//_viewMatrix = XMMatrixLookAtLH(_destination, _target->_translation, V_UP);


	//위치만 따라감
	//_destination = _target->_translation - V_FORWARD * _distance + V_UP * _height;

	//_transform->_translation = _destination;

	//_viewMatrix = XMMatrixLookAtLH(_destination, _target->_translation, V_UP);
	
	//damping 적용
	_destRot = LERP(_destRot, _target->_rotation.y, _rotDamping * Time::Delta());

	XMMATRIX rotMatrix = XMMatrixRotationY(_destRot + _rotY);

	Vector3 forward = V_FORWARD * rotMatrix;

	_destination = _target->GetGlobalPosition() + forward * _distance + V_UP * _height;

	_transform->_translation = LERP(_transform->_translation, _destination, _moveDamping * Time::Delta());

	_viewMatrix = XMMatrixLookAtLH(_transform->_translation, _target->_translation, V_UP);

	SetView();
}

void Camera::SetView()
{
	_transform->Update();

	//XMVECTOR eyePos   = _transform->_translation;
	//XMVECTOR focusPos = _transform->_translation + _transform->Forward();
	//XMVECTOR upVector = _transform->Up();

	//_viewMatrix = XMMatrixLookAtLH(eyePos, focusPos, upVector);

	_viewBuffer->SetData(_viewMatrix, _transform->GetWorld());
	_viewBuffer->SetVSBuffer(1);
}

void Camera::Save()
{
	BinaryWriter data(L"CameraData");

	data.WriteData(_transform->_scale);
	data.WriteData(_transform->_rotation);
	data.WriteData(_transform->_translation);
}

void Camera::Load()
{
	BinaryReader data(L"CameraData");

	if (!data.Succeeded())
		return;

	_transform->_scale		 = data.ReadVector3();
	_transform->_rotation	 = data.ReadVector3();
	_transform->_translation = data.ReadVector3();
}
