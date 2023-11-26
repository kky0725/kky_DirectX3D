#include "Framework.h"
#include "Groot.h"

Groot::Groot()
	:ModelAnimator("Groot")
{
	_scale *= 0.04f;
	ReadClip("Sad Idle");
	ReadClip("Running");
	ReadClip("Mutant Swiping");
	CreateTexture();

	_reader->GetMaterial()[0]->Load(L"groot.mat");

	_weapon = new Model(name);
	_weapon->GetReader()->GetMaterial()[0]->Load(L"warven_Axe.mat");
	_weapon->_rotation.y = XMConvertToRadians(61.0f);
	_weapon->_rotation.z = XMConvertToRadians(195.0f);
	_weapon->_translation = { -2.0f, 60.0f, -20.0f };
	//_weapon->_scale = Vector3(100.0f, 100.0f, 100.0f);

	_lefthand = new Transform();
	_weapon->SetParent(_lefthand);
	
	_clips[ATTACK]->SetEndEvent(0.7f, std::bind(&Groot::SetClip, this, IDLE));

	_hpBar = new ProgressBar(L"UI/hp_bar.png", L"UI/hp_bar_BG.png");
	_hpBar->SetLabel("Hp Bar");
	_hpBar->_scale.x *= 0.5f;
}

Groot::~Groot()
{
	delete _weapon;
	delete _lefthand;

	delete _hpBar;
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

	_hpBar->Update();
	_hpBar->_translation = CAMERA->WorldToScreenPoint(this->_globalPosition + V_UP * 10);

	UpdateLeftHand();
	//Move();
}

void Groot::Render()
{
	ModelAnimator::Render();

	_weapon->Render();
}

void Groot::PostRender()
{
	Debug();
	_hpBar->Render();
}

void Groot::Debug()
{
	ModelAnimator::Debug();

	ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
	ImGui::SliderFloat("TakeTime", &takeTime, 0.0f, 1.0f);
	
	_weapon->Debug();

	Transform::Debug();
	//_label = "Groot";
	_ID = "Groot";

	static float value = 1.0f;

	_hpBar->SetValue(value);

	ImGui::SliderFloat("HP", &value, 0.0f, 1.0f);

}

void Groot::UpdateLeftHand()
{
	UINT nodeIndex = _reader->GetNodeIndex("mixamorig:LeftHand");

	Matrix nodeTransform = GetTransformByNode(nodeIndex);

	_lefthand->GetWorld() = nodeTransform * _world;
}

void Groot::SetClip(AnimState state)
{
	if (_curState != state)
	{
		PlayClip(state);
		_curState = state;
	}
}

void Groot::Move()
{
	if (KEY_PRESS('W'))
	{
		_translation -= Forward() * _moveSpeed * Time::Delta();
		SetClip(RUN);
	}

	if (KEY_PRESS('S'))
	{
		_translation -= Backward() * _moveSpeed * Time::Delta();
		SetClip(RUN);
	}

	if (KEY_UP('W') || KEY_UP('S'))
		SetClip(IDLE);

	if (KEY_PRESS('A'))
	{
		_rotation.y -= _rotSpeed * Time::Delta();
	}

	if (KEY_PRESS('D'))
	{
		_rotation.y += _rotSpeed * Time::Delta();
	}

	if (KEY_DOWN(VK_LBUTTON))
	{
		SetClip(ATTACK);
	}
}
