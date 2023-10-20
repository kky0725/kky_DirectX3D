#include "Framework.h"
#include "Groot.h"

Groot::Groot()
	:ModelAnimator("Groot")
{
	_scale *= 0.1f;
	ReadClip("Sad Idle");
	ReadClip("Running");
	ReadClip("Mutant Swiping");
	CreateTexture();

	_reader->GetMaterial()[0]->Load(L"groot.mat");

	_weapon = new Sphere();
	_weapon->_scale = Vector3(100.0f, 100.0f, 100.0f);

	_lefthand = new Transform();
	_weapon->SetParent(_lefthand);
}

Groot::~Groot()
{
	delete _weapon;
	delete _lefthand;
}

void Groot::Update()
{
	ModelAnimator::Update();
	_weapon->Update();
	//_lefthand->Update();

	if (KEY_DOWN('1'))
		PlayClip(0, speed, takeTime);

	if (KEY_DOWN('2'))
		PlayClip(1, speed, takeTime);

	if (KEY_DOWN('3'))
		PlayClip(2, speed, takeTime);

	UpdateLeftHand();
}

void Groot::Render()
{
	ModelAnimator::Render();

	_weapon->Render();
}

void Groot::Debug()
{
	ModelAnimator::Debug();

	ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
	ImGui::SliderFloat("TakeTime", &takeTime, 0.0f, 1.0f);

	_weapon->Debug();
}

void Groot::UpdateLeftHand()
{
	UINT nodeIndex = _reader->GetNodeIndex("mixamorig:LeftHand");

	Matrix nodeTransform = GetTransformByNode(nodeIndex);

	_lefthand->GetWorld() = nodeTransform * _world;
}
