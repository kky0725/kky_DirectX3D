#pragma once
class Camera : public Singleton<Camera>
{
	friend class Singleton;
public:
	enum Mode
	{
		MODE1, MODE2
	};


private:
	Camera();
	~Camera();

public:
	void Update();
	void Debug();

	Transform* GetTransform() { return _transform; }
	
	Ray ScreenPointToRay(Vector3 screenPos);
	Vector3 WolrdToScreenPoint(Vector3 worldPos);

	void SetTarget(Transform* target) { this->_target = target; }

private:
	void FreeMode();
	void TargetMode(Mode mode = MODE1);
	
	void SetView();

	void Save();
	void Load();

private:
	Transform* _transform;

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

};