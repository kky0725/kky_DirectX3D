#pragma once
class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

	void CreateRobot();
	void CreatePart(Vector4 color, Vector3 pos, Vector3 scale = Vector3(1.0f, 1.0f, 1.0f), Cube* parent = nullptr);

	void Move();

private:
	vector<Cube*> _robot;
	bool _rightUp = true;
};