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
	Transform::UpdateWorld();

	Vector3 O = ray.origin;
	Vector3 D = ray.direction;
	Vector3 P = this->_globalPosition;
	Vector3 X = O - P;

	float a = Vector3::Dot(D,D);
	float b = 2 * Vector3::Dot(D,X);
	float c = Vector3::Dot(X,X) - pow(Radius(), 2);

	//float theta = acos(Vector3::Dot(D,X) /X.Length());

	//if (X.Length() * sin(theta) <= Radius())
	//	return true;

	if (pow(b, 2) - 4 * a * c >= 0)
	{
		if(contact != nullptr)
		{
			float t = (-b - sqrt(pow(b,2) - 4 * a * c)) / (2 * a);

			contact->distance = t;
			contact->hitPoint = O + D * t;
		}
		return true;
	}

	return false;
}

bool ColliderSphere::Collision(ColliderBox* other)
{
	return other->Collision(this);
}

bool ColliderSphere::Collision(ColliderSphere* other)
{
	float distance = Distance(this->_globalPosition, other->_globalPosition);

	return distance<= this->Radius() + other->Radius();
}

bool ColliderSphere::Collision(ColliderCapsule* other)
{
	return other->Collision(this);
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
