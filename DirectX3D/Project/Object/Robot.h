#pragma once
class Robot
{
public:
	Robot();
	~Robot();

	void Update();
	void Render();

	void SetPosition(Vector3 pos);

private:
	void CreateRobot();
	void CreatePart(Vector4 color, Vector3 pos, Vector3 scale = Vector3(1.0f, 1.0f, 1.0f), Cube* parent = nullptr);
	void Move();

private:
	vector<Cube*> _robot;
	bool _rightUp = true;
};