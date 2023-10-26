#include "Framework.h"
#include "ColliderBox.h"

ColliderBox::ColliderBox(Vector3 size)
	:_size(size)
{
	_type = BOX;

	CreateMesh();
}

ColliderBox::~ColliderBox()
{
}

bool ColliderBox::Collision(IN Ray& ray, OUT Contact* contact)
{
	return false;
}

bool ColliderBox::Collision(ColliderBox* other)
{
	Obb box1 = this->GetOBB();
	Obb box2 = other->GetOBB();

	Vector3 D = box2.position - box1.position;

	for (UINT i = 0; i < 3; i++)
	{
		if (SeparatedAxis(D, box1.axis[i], box1, box2)) return false;
		if (SeparatedAxis(D, box2.axis[i], box1, box2)) return false;
	}

	for (UINT i = 0; i < 3; i++)
	{
		for (UINT j = 0; j < 3; j++)
		{
			if (box1.axis[i] == box2.axis[j]) return true;
		}
	}

	for (UINT i = 0; i < 3; i++)
	{
		for (UINT j = 0; i < 3; i++)
		{
			Vector3 cross = Vector3::Cross(box1.axis[i], box2.axis[j]);

			if (SeparatedAxis(D, cross, box1, box2)) return true;
		}
	}
	return false;
}

bool ColliderBox::Collision(ColliderSphere* other)
{
	return false;
}

bool ColliderBox::Collision(ColliderCapsule* other)
{
	return false;
}

ColliderBox::Obb ColliderBox::GetOBB()
{
	Obb obb;
	obb.position = this->_globalPosition;

	obb.axis[0] = this->_right;
	obb.axis[1] = this->_up;
	obb.axis[2] = this->_forward;

	obb.halfSize = _size * 0.5f * _globalScale;

	return obb;
}

bool ColliderBox::SeparatedAxis(Vector3 D, Vector3 axis, Obb box1, Obb box2)
{
	float distance = abs(Vector3::Dot(D, axis));
	float sum = 0.0f;

	for (UINT i = 0; i < 3; i++)
	{
		sum += abs(Vector3::Dot(box1.axis[i] * box1.halfSize[i], axis));
		sum += abs(Vector3::Dot(box2.axis[i] * box2.halfSize[i], axis));
	}

	return distance > sum;
}

void ColliderBox::CreateMesh()
{
	Vector3 halfSize = _size * 0.5f;

	_vertices =
	{
		{-halfSize.x, +halfSize.y, -halfSize.z},
		{+halfSize.x, +halfSize.y, -halfSize.z},
		{-halfSize.x, -halfSize.y, -halfSize.z},
		{+halfSize.x, -halfSize.y, -halfSize.z},

		{-halfSize.x, +halfSize.y, +halfSize.z},
		{+halfSize.x, +halfSize.y, +halfSize.z},
		{-halfSize.x, -halfSize.y, +halfSize.z},
		{+halfSize.x, -halfSize.y, +halfSize.z}
	};

	_indices =
	{
		0,1, 2,3, 4,5, 6,7,
		0,4, 1,5, 2,6, 3,7,
		0,2, 1,3, 4,6, 5,7
	};

	_mesh = new Mesh(_vertices, _indices);
}


