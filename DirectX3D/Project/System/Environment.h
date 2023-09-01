#pragma once
class Environment : public Singleton<Environment>
{
	friend class Singleton;
	Environment();
	~Environment();

	void CreateViewport();
	void CreatePerspective();
public:
	void SetEnvironment();

	void PostRneder();

private:
	MatrixBuffer* _projectionBuffer;

	LightBuffer* _lightBuffer;

	Vector3 _lightDirection = V_DOWN;
};
