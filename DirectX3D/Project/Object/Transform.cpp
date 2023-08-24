#include "Framework.h"
#include "Transform.h"

Transform::Transform()
{
	_world = XMMatrixIdentity();
}

Transform::~Transform()
{
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

