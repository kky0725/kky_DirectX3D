#pragma once
class Camera;

class Environment : public Singleton<Environment>
{
	friend class Singleton;
	Environment();
	~Environment();

	void CreatePerspective();
	void CreateOrthographic();

	void DebugLight(int lightIndex);

public:
	void SetViewport(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	void SetEnvironment();
	void PostSet();

	void PostRneder();

	Matrix GetPersMatrix() { return _PersMatrix; }
	MatrixBuffer* GetPersBuffer() { return _persBuffer; }

	Camera* GetMainCamera() { return _mainCamera; }

	LightBuffer* GetLightBuffer() { return _lightBuffer; }

private:
	MatrixBuffer* _persBuffer;
	Matrix		  _PersMatrix;

	MatrixBuffer* _orthoBuffer;
	Matrix		  _orthoMatrix;

	ViewBuffer* _UIViewBuffer;

	LightBuffer* _lightBuffer;

	Camera* _mainCamera;
};
