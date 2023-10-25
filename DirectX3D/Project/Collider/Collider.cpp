#include "Framework.h"
#include "Collider.h"

bool Collider::_hiddenInGame = false;

Collider::Collider()
{
	_material = new Material(L"03Collider");

	SetColor(0.0f, 1.0f, 0.0f);
}

Collider::~Collider()
{
	delete _material;
	delete _mesh;
}

bool Collider::Collision(Collider* other)
{
	Transform::UpdateWorld();
		other->UpdateWorld();
	
	switch (other->_type)
	{
	case Collider::BOX:
		return Collision((ColliderBox*)other);
		break;
	case Collider::SPHERE:
		return Collision((ColliderSphere*)other);
		break;
	case Collider::CAPSULE:
		return Collision((ColliderCapsule*)other);
		break;
	default:
		break;
	}

	return false;
}

void Collider::Render()
{
	if (_hiddenInGame)
		return;
	Transform::SetWorld();

	_mesh->SetMesh(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	_material->SetMaterial();

	DC->DrawIndexed(_indices.size(), 0, 0);
}
