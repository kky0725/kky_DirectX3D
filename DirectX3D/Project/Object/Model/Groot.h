#pragma once
class Groot : public ModelAnimator
{
public:
	Groot();
	~Groot();

	virtual void Update();
	virtual void Render();

	virtual void Debug();

	void UpdateLeftHand();

private:

	float speed = 1.0f;
	float takeTime = 0.2f;

	Sphere* _weapon;

	Transform* _lefthand;
};