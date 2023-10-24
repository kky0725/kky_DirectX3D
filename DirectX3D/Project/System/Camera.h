#pragma once

struct Ray
{
	Vector3 origion;
	Vector3 direction;
};

class Camera : public Singleton<Camera>
{
	friend class Singleton;
	Camera();
	~Camera();

public:
	void Update();
	void Debug();

	Transform* GetTransform() { return _transform; }
	
	Ray ScreenPointToRay(Vector3 screenPos);

	void SetTarget(Transform* target) { this->_target = target; }

private:
	void FreeMode();
	void TargetMode();
	
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
	float _height = 60.0f;
	Vector3 _destination;
	Vector3 _focusOffset;

	float _rotY = 0.0f;
	float _destRot = 0.0f;

	float _moveDamping = 5.0f;
	float _rotDamping = 1.0f;

};