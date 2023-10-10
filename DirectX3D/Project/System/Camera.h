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
	Matrix		  _viewMatrix;

	Vector3 _oldPos;
};