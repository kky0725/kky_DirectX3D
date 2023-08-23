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
}

