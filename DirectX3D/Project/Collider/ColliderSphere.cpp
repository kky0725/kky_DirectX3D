#include "Framework.h"
#include "ColliderSphere.h"

ColliderSphere::ColliderSphere(float radius, UINT stackCount, UINT sliceCount)
	:_radius(radius), _stackCount(stackCount), _sliceCount(sliceCount)
{
	_type = SPHERE;
	CreateMesh();
}

ColliderSphere::~ColliderSphere()
{
}

bool ColliderSphere::Collision(IN Ray& ray, OUT Contact* contact)
{
	return false;
}

bool ColliderSphere::Collision(ColliderBox* other)
{
	return false;
}

bool ColliderSphere::Collision(ColliderSphere* other)
{
	float distance = Distance(this->_globalPosition, other->_globalPosition);

	return distance<= this->Radius() + other->Radius();
}

bool ColliderSphere::Collision(ColliderCapsule* other)
{
	return false;
}

void ColliderSphere::CreateMesh()
{
	for (int i = 0; i <= _stackCount; i++)
	{
		float phi = i * XM_PI / _stackCount;

		for (int j = 0; j <= _sliceCount; j++)
		{
			VertexType vertex;
			float theta = j * XM_2PI / _sliceCount;

			vertex.pos.x = _radius * sin(phi) * cos(theta);
			vertex.pos.y = _radius * cos(phi);
			vertex.pos.z = _radius * sin(phi) * sin(theta);

			_vertices.push_back(vertex);
		}
	}

	for (int j = 0; j < _stackCount; j++)//stack
	{
		for (int i = 0; i < _sliceCount; i++)//slice
		{
			_indices.push_back(i + 0 + (_sliceCount + 1) * (j + 0));
			_indices.push_back(i + 1 + (_sliceCount + 1) * (j + 0));

			_indices.push_back(i + 0 + (_sliceCount + 1) * (j + 0));
			_indices.push_back(i + 0 + (_sliceCount + 1) * (j + 1));
		}
	}

	_mesh = new Mesh(_vertices, _indices);
}
