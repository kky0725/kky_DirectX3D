#include "Framework.h"
#include "Transform.h"

UINT Transform::_index = 0;

Transform::Transform()
{
	_world = XMMatrixIdentity();
	
	_worldBuffer = new WorldBuffer();

	_ID = "Object_" + to_string(++_index);
}

Transform::~Transform()
{
	delete _worldBuffer;
}

void Transform::Update()
{
	UpdateWorld();
}

void Transform::UpdateWorld()
{
	_world = XMMatrixTransformation
	(
		_pivot, XMQuaternionIdentity(), _scale,
		_pivot, XMQuaternionRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z),
		_translation
	);

	if (_parent != nullptr)
		_world *= _parent->_world;

	XMFLOAT4X4 fWorld;

	XMStoreFloat4x4(&fWorld, _world);

	_right		= Vector3(fWorld._11, fWorld._12, fWorld._13).GetNormalized();
	_up			= Vector3(fWorld._21, fWorld._22, fWorld._23).GetNormalized();
	_forward	= Vector3(fWorld._31, fWorld._32, fWorld._33).GetNormalized();

	XMVECTOR outS, outR, outT;

	XMMatrixDecompose(&outS, &outR, &outT, _world);

	_globalScale	= outS;
	_globalRotation = outR;
	_globalPosition = outT;
}

void Transform::Debug()
{
	if (ImGui::BeginMenu(_ID.c_str()))
	{
		ImGui::DragFloat3("Scale", (float*)&_scale, 0.01f, 0.01f, 100.0f);
		//ImGui::DragFloat3("Rotation",	 (float*)&_rotation,	0.01f, -XM_2PI, +XM_2PI);
		ImGui::SliderAngle("Rotationx", &_rotation.x);//270에서 짐벌락 현상 발생->쿼터니언 각도를 사용해서 해결 가능
		ImGui::SliderAngle("Rotationy", &_rotation.y);
		ImGui::SliderAngle("Rotationz", &_rotation.z);
		ImGui::DragFloat3("Translation", (float*)&_translation, 0.01f, -WIN_WIDTH, WIN_WIDTH);

		ImGui::EndMenu();
	}
}

void Transform::SetWorld(int hasAnimation)
{
	_worldBuffer->SetData(_world, hasAnimation);
	_worldBuffer->SetVSBuffer(0);
}

