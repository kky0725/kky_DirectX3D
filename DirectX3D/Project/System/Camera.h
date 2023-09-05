#pragma once
class Camera : public Singleton<Camera>
{
	friend class Singleton;
	Camera();
	~Camera();

public:
	void Update();
	void PostRender();

	Transform* GetTransform() { return _transform; }

private:
	void FreeMode();
	void TargetMode();
	
	void SetView();

private:
	Transform* _transform;

	float _moveSpeed = 20.0f;
	float  _rotSpeed = 5.0f;

	ViewBuffer* _viewBuffer;
	Matrix		  _viewMatrix;

	Vector3 _oldPos;
};