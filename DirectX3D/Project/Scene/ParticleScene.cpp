#include "Framework.h"
#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
	_collider = new ColliderSphere(50);
	//_particle = new Sprite(L"Effect/greenCore_4x4.png", Vector2(30, 30), 4, 4, true);
	//_particle = new Spark(L"Effect/Star.png", true);
	_particle = new Rain();
	_particle->Play(Vector3{0,0,0});

}

ParticleScene::~ParticleScene()
{
	delete _collider;
	delete _particle;
}

void ParticleScene::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Ray ray = CAMERA->ScreenPointToRay(mousePos);

		Contact contact;

		if (_collider->Collision(ray, &contact))
		{
			//_particle->Play(contact.hitPoint);
		}
	}

	_collider->Update();
	_particle->Update();
}

void ParticleScene::PreRender()
{
}

void ParticleScene::Render()
{
	_collider->Render();
	_particle->Render();
}

void ParticleScene::PostRender()
{
	_particle->Debug();
}


