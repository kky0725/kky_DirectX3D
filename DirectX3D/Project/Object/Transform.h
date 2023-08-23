#pragma once
class Transform
{
public:
	Transform();
	virtual ~Transform();

	void Update();
	void UpdateWorld();

	Matrix& GetWorld() { return _world; }

	void SetParent(Transform* parent) { this->_parent = parent; }

public:
	Vector3 _scale			= { 1.0f, 1.0f, 1.0f };
	Vector3 _rotation		= { 0.0f, 0.0f, 0.0f };
	Vector3 _translation	= { 0.0f, 0.0f, 0.0f };

protected:
	Matrix _world;

	Vector3 _pivot = {};

	Transform* _parent = nullptr;
};
