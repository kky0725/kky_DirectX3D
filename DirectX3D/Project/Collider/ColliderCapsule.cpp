#include "Framework.h"
#include "ColliderCapsule.h"

ColliderCapsule::ColliderCapsule()
{
}

ColliderCapsule::~ColliderCapsule()
{
}

bool ColliderCapsule::Collision(IN Ray& ray, OUT Contact* contact)
{
	return false;
}

bool ColliderCapsule::Collision(ColliderBox* other)
{
	return false;
}

bool ColliderCapsule::Collision(ColliderSphere* other)
{
	return false;
}

bool ColliderCapsule::Collision(ColliderCapsule* other)
{
	return false;
}

void ColliderCapsule::CreateMesh()
{
}
