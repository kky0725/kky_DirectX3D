#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	for (UINT i = 0; i < 2; i++)
	{
		_colliders.emplace_back(new ColliderSphere);
		_colliders[i]->SetLabel("ColliderSphere" + to_string(i));
		_colliders[i]->_translation.x = 2 * i;
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

	if (_colliders[0]->Collision(_colliders[1]))
		_colliders[0]->SetColor(1, 0, 0);
	else
		_colliders[0]->SetColor(0, 1, 0);
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


