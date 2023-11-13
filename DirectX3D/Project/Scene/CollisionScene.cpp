#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	for (UINT i = 0; i < 2; i++)
	{
		_colliders.emplace_back(new ColliderSphere);
		_colliders[i]->SetLabel("ColliderSphere" + to_string(i));
		_colliders[i]->_translation.x = 3 * i;
	}
	for (UINT i = 2; i < 4; i++)
	{
		_colliders.emplace_back(new ColliderBox);
		_colliders[i]->SetLabel("ColliderBox" + to_string(i));
		_colliders[i]->_translation.x = 3 * i;
	}
}

CollisionScene::~CollisionScene()
{
	for (Collider* collider : _colliders)
		delete collider;

	_colliders.clear();
}

void CollisionScene::Update()
{
	for (Collider* collider : _colliders)
		collider->Update();

	Ray ray = CAMERA->ScreenPointToRay(mousePos);

	static Contact contact;

	if (_colliders[2]->Collision(_colliders[1]))
		_colliders[2]->SetColor(1, 0, 0);
	else
		_colliders[2]->SetColor(0, 1, 0);

	//_colliders[1]->_translation = contact.hitPoint;
}

void CollisionScene::PreRender()
{
}

void CollisionScene::Render()
{
	for (Collider* collider : _colliders)
		collider->Render();
}

void CollisionScene::PostRender()
{
	for (Collider* collider : _colliders)
		collider->Debug();
}


