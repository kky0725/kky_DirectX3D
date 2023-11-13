#pragma once
class Camera : public Transform
{
public:
	enum Mode
	{
		MODE1, MODE2
	};

public:
	Camera();
	~Camera();

	void Update();
	void Debug();

	Ray ScreenPointToRay(Vector3 screenPos);
	Vector3 WolrdToScreenPoint(Vector3 worldPos);

	void SetTarget(Transform* target) { this->_target = target; }

	ViewBuffer* GetViewBuffer() { return _viewBuffer; }

	bool ContainPoint(Vector3 point);
	bool ContainSphere(Vector3 center, float radius);

private:
	void FreeMode();
	void TargetMode(Mode mode = MODE1);
	
	void SetView();

	void Save();
	void Load();

	void CalculateFrustum();

private:

	float _moveSpeed = 20.0f;
	float  _rotSpeed = 5.0f;

	ViewBuffer* _viewBuffer;
	Matrix		_viewMatrix;

	Vector3 _oldPos;

	Transform* _target = nullptr;
	float _distance = 60.0f;
	float _height = 10.0f;
	Vector3 _destination;
	Vector3 _focusOffset;

	float _rotY = 0.0f;
	float _destRotY = 0.0f;
	//float _rotX = 0.0f;
	float _destRotX = 0.0f;

	float _moveDamping = 30.0f;
	float _rotDamping = 30.0f;

	XMVECTOR _planes[6];
	float _a, _b, _c, _d;
};