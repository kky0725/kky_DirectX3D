#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	_viewBuffer = new ViewBuffer();

	_translation = { 60.0f, 100.0f, -80.0f };
	//_translation = { 0.0f, 0.0f, -20.0f };
	_rotation.x = 0.65f;

	Load();
}

Camera::~Camera()
{
	Save();

	delete _viewBuffer;
}

void Camera::Update()
{
	CalculateFrustum();

	if(!_target)
		FreeMode();
	else
		TargetMode(MODE2);

	SetView();
}

void Camera::Debug()
{
	ImGuiIO io = ImGui::GetIO();
	_distance -= io.MouseWheel * _moveSpeed;

	if (ImGui::TreeNode("Camera Option"))
	{
		Vector3 pos = _translation;
		Vector3 rot = _rotation;

		ImGui::Text("Camera Pos x : %.3f, y : %.3f, z : %.3f", pos.x, pos.y, pos.z);
		ImGui::Text("Camera Rot x : %.3f, y : %.3f, z : %.3f", rot.x, rot.y, rot.z);
		
		Transform::Debug();

		ImGui::SliderFloat("Height", &_height, -10.0f, 100.0f);
		ImGui::SliderFloat("Distance", &_distance, -10.0f, 100.0f);

		ImGui::SliderFloat("Camera RotY", &_rotY, 0.0f, XM_2PI);

		ImGui::SliderFloat("Camera MoveDamping", &_moveDamping, 0.0f, 30.0f);
		ImGui::SliderFloat("Camera RotDamping", &_rotDamping, 0.0f, 30.0f);

		ImGui::TreePop();
	}
}

Ray Camera::ScreenPointToRay(Vector3 screenPos)
{
	Ray ray;
	ray.origin = Transform::_translation;

	//////InvViewport/////// LeftTop이 0,0이라는 가정

	Vector3 point;

	point.x = +(2.0f * screenPos.x) / WIN_WIDTH - 1.0f;
	point.y = -(2.0f * screenPos.y) / WIN_HEIGHT + 1.0f;
	point.z = 1.0f;//FarZ

	///////Invprojection///////

	Matrix projection = Environment::GetInstance()->GetPersMatrix();

	XMFLOAT4X4 proj;
	XMStoreFloat4x4(&proj, projection);

	point.x /= proj._11;
	point.y /= proj._22;

	////InvView/////

	Matrix invView = Transform::GetWorld();
	//if (_target)
		//invView = XMMatrixInverse();

	ray.direction = point * invView;
	ray.direction.Normalize();

	return ray;
}

Vector3 Camera::WorldToScreenPoint(Vector3 worldPos)
{
	Vector3 screenPos;

	screenPos = XMVector3TransformCoord(worldPos, _viewMatrix);
	screenPos = XMVector3TransformCoord(screenPos, Environment::GetInstance()->GetPersMatrix());

	screenPos = (screenPos + Vector3(1, 1, 1)) * 0.5f;

	screenPos.x *= WIN_WIDTH;
	screenPos.y *= WIN_HEIGHT;


	return screenPos;
}

bool Camera::ContainPoint(Vector3 point)
{
	for (UINT i = 0; i < 6; i++)
	{
		Vector3 dot = XMPlaneDotCoord(_planes[i], point);

		if (dot.x < 0.0f)
			return false;
	}
	return true;
}

bool Camera::ContainSphere(Vector3 center, float radius)
{
	Vector3 edge;
	Vector3 dot;

	for (UINT i = 0; i < 6; i++)
	{
		edge.x = center.x - radius;
		edge.y = center.y - radius;
		edge.z = center.z - radius;

		dot = XMPlaneDotCoord(_planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x + radius;
		edge.y = center.y - radius;
		edge.z = center.z - radius;

		dot = XMPlaneDotCoord(_planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x - radius;
		edge.y = center.y + radius;
		edge.z = center.z - radius;

		dot = XMPlaneDotCoord(_planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x - radius;
		edge.y = center.y - radius;
		edge.z = center.z + radius;

		dot = XMPlaneDotCoord(_planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x + radius;
		edge.y = center.y + radius;
		edge.z = center.z - radius;

		dot = XMPlaneDotCoord(_planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x + radius;
		edge.y = center.y - radius;
		edge.z = center.z + radius;

		dot = XMPlaneDotCoord(_planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x - radius;
		edge.y = center.y + radius;
		edge.z = center.z + radius;

		dot = XMPlaneDotCoord(_planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x + radius;
		edge.y = center.y + radius;
		edge.z = center.z + radius;

		dot = XMPlaneDotCoord(_planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		return false;
	}

	return true;
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
			Transform::_translation += Transform::Left() * _moveSpeed * Time::Delta();

		if (KEY_PRESS('D'))
			Transform::_translation += Transform::Right() * _moveSpeed * Time::Delta();

		if (KEY_PRESS('S'))
			Transform::_translation += Transform::Backward() * _moveSpeed * Time::Delta();

		if (KEY_PRESS('W'))
			Transform::_translation += Transform::Forward() * _moveSpeed * Time::Delta();

		if (KEY_PRESS('Q'))
			Transform::_translation += Transform::Up() * _moveSpeed * Time::Delta();

		if (KEY_PRESS('E'))
			Transform::_translation += Transform::Down() * _moveSpeed * Time::Delta();
	
		Vector3 dir = mousePos - _oldPos;

		if (abs(dir.x) > 15.0f || abs(dir.y) > 15.0f)
			dir = Vector3(0.0f, 0.0f, 0.0f);

		Transform::_rotation.y += dir.x * _rotSpeed * Time::Delta();
		Transform::_rotation.x += dir.y * _rotSpeed * Time::Delta();
	}

	_oldPos = mousePos;

	_viewMatrix = XMMatrixInverse(nullptr, Transform::GetWorld());

	SetView();
}

void Camera::TargetMode(Mode mode)
{
	if (KEY_PRESS(VK_UP))
		_height += _moveSpeed * Time::Delta();

	if (KEY_PRESS(VK_DOWN))
		_height -= _moveSpeed * Time::Delta();

	switch (mode)
	{
	case Camera::MODE1:
	{
		_destRotY = LERP(_destRotY, _target->_rotation.y + XM_PI, _rotDamping * Time::Delta());

		XMMATRIX rotMatrix = XMMatrixRotationY(_destRotY + _rotY);

		Vector3 forward = V_BACKWARD * rotMatrix;

		_destination = _target->GetGlobalPosition() + forward * _distance + V_UP * _height;

		Transform::_translation = LERP(Transform::_translation, _destination, _moveDamping * Time::Delta());

		_viewMatrix = XMMatrixLookAtLH(Transform::_translation, _target->_translation, V_UP);
	}
		break;
	case Camera::MODE2:
	{
		if (KEY_PRESS(VK_RBUTTON))
		{
			Vector3 dir = mousePos - _oldPos;

			Transform::_rotation.y += dir.x * _rotSpeed * Time::Delta();
			Transform::_rotation.x += dir.y * _rotSpeed * Time::Delta();
		}
		_oldPos = mousePos;

		_destRotY = LERP(_destRotY, Transform::_rotation.y, _rotDamping * Time::Delta());
		_destRotX = LERP(_destRotY, Transform::_rotation.x, _rotDamping * Time::Delta());

		XMMATRIX rotMatrix = XMMatrixRotationRollPitchYaw(_destRotX, _destRotY + _rotY, 0.0f);

		Vector3 forward = V_FORWARD * rotMatrix;

		_destination = _target->GetGlobalPosition() + forward * _distance;

		Transform::_translation = LERP(Transform::_translation, _destination, _moveDamping * Time::Delta());

		_viewMatrix = XMMatrixLookAtLH(Transform::_translation, _target->_translation, V_UP);

		_viewMatrix *= XMMatrixTranslation(0, -_height, 0);
	}
		break;
	default:
		break;
	}

	SetView();

}


void Camera::SetView()
{
	Transform::Update();

	//XMVECTOR eyePos   = Transform::_translation;
	//XMVECTOR focusPos = Transform::_translation + Transform::Forward();
	//XMVECTOR upVector = Transform::Up();

	//_viewMatrix = XMMatrixLookAtLH(eyePos, focusPos, upVector);

	_viewMatrix = XMMatrixInverse(nullptr, _world);
	_viewBuffer->SetData(_viewMatrix, Transform::GetWorld());
	_viewBuffer->SetVSBuffer(1);
}

void Camera::Set()
{
	_viewMatrix = XMMatrixInverse(nullptr, _world);
	_viewBuffer->SetData(_viewMatrix, Transform::GetWorld());
}

void Camera::Save()
{
	BinaryWriter data(L"CameraData");

	data.WriteData(Transform::_scale);
	data.WriteData(Transform::_rotation);
	data.WriteData(Transform::_translation);
}

void Camera::Load()
{
	BinaryReader data(L"CameraData");

	if (!data.Succeeded())
		return;

	Transform::_scale		= data.ReadVector3();
	Transform::_rotation	= data.ReadVector3();
	Transform::_translation = data.ReadVector3();
}

void Camera::CalculateFrustum()
{
	XMFLOAT4X4 VP;
	XMStoreFloat4x4(&VP, _viewMatrix * Environment::GetInstance()->GetPersMatrix());

	//LEFT
	_a = VP._14 + VP._11;
	_b = VP._24 + VP._21;
	_c = VP._34 + VP._31;
	_d = VP._44 + VP._41;

	_planes[0] = XMVectorSet(_a, _b, _c, _d);

	//RIGHT
	_a = VP._14 - VP._11;
	_b = VP._24 - VP._21;
	_c = VP._34 - VP._31;
	_d = VP._44 - VP._41;

	_planes[1] = XMVectorSet(_a, _b, _c, _d);

	//BOTTOM
	_a = VP._14 + VP._12;
	_b = VP._24 + VP._22;
	_c = VP._34 + VP._32;
	_d = VP._44 + VP._42;

	_planes[2] = XMVectorSet(_a, _b, _c, _d);

	//TOP
	_a = VP._14 - VP._12;
	_b = VP._24 - VP._22;
	_c = VP._34 - VP._32;
	_d = VP._44 - VP._42;

	_planes[3] = XMVectorSet(_a, _b, _c, _d);

	//Near
	_a = VP._14 + VP._13;
	_b = VP._24 + VP._23;
	_c = VP._34 + VP._33;
	_d = VP._44 + VP._43;

	_planes[4] = XMVectorSet(_a, _b, _c, _d);

	//Far
	_a = VP._14 - VP._13;
	_b = VP._24 - VP._23;
	_c = VP._34 - VP._33;
	_d = VP._44 - VP._43;

	_planes[5] = XMVectorSet(_a, _b, _c, _d);

	for (UINT i = 0; i < 6; i++)
	{
		_planes[i] = XMPlaneNormalize(_planes[i]);
	}
}
