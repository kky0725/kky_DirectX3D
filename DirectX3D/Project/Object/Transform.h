#pragma once
class Transform
{
public:
	Transform();
	virtual ~Transform();

	virtual void Update();
	void UpdateWorld();

	Matrix& GetWorld() { return _world; }

	void SetParent(Transform* parent) { this->_parent = parent; }

	Vector3	 Forward() { return _forward; }
	Vector3 Backward() { return _forward * -1; }
	Vector3	    Left() { return _right * -1; }
	Vector3	   Right() { return _right; }
	Vector3		  Up() { return _up; }
	Vector3		Down() { return _up * -1; }

	void Debug();
	void SetLabel(string label) { this->_ID = label; }

public:
	Vector3 _scale			= { 1.0f, 1.0f, 1.0f };
	Vector3 _rotation		= { 0.0f, 0.0f, 0.0f };
	Vector3 _translation	= { 0.0f, 0.0f, 0.0f };

protected:
	Matrix _world;

	Vector3 _pivot = {};

	Transform* _parent = nullptr;

	Vector3 _globalScale;
	Vector3 _globalRotation;
	Vector3 _globalPosition;

	Vector3 _right, _up, _forward;

	string _ID = "";
};
