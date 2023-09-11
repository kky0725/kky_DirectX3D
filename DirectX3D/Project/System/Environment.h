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

	Matrix GetProjMatirx() { return _projectionMatrix; }

private:
	MatrixBuffer* _projectionBuffer;
	Matrix		  _projectionMatrix;

	LightBuffer* _lightBuffer;
};
