#pragma once
class Groot : public ModelAnimator
{
	enum AnimState
	{
		IDLE, RUN, ATTACK
	} _curState = IDLE;

public:
	Groot();
	~Groot();

	virtual void Update();
	virtual void Render();
	void PostRender();

	virtual void Debug();

	void UpdateLeftHand();

	void SetClip(AnimState state);

private:
	void Move();

private:

	float speed = 1.0f;
	float takeTime = 0.2f;

	string name = "Dwarven_Axe";

	Model* _weapon;

	Transform* _lefthand;

	float _moveSpeed = 10.0f;
	float _rotSpeed = 3.0f;

	ProgressBar* _hpBar;
};