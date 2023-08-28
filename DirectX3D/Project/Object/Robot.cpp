#include "Framework.h"
#include "Robot.h"

Robot::Robot()
{
	CreateRobot();
}

Robot::~Robot()
{
	for (Cube* part : _robot)
		delete part;
}

void Robot::Update()
{
	for (Cube* part : _robot)
		part->Update();

	Move();
}

void Robot::Render()
{
	for (Cube* part : _robot)
		part->Render();
}

void Robot::CreateRobot()
{
	//head 0
	CreatePart(Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector3(0.0f, 2.0f, 0.0f), Vector3(0.5f, 0.5f, 0.5f));
	//body 1
	CreatePart(Vector4(0.5f, 0.5f, 0.5f, 1.0f), Vector3(0.0f, -3.5f, 0.0f), Vector3(1.0f, 2.0f, 1.0f), _robot[0]);

	//RightArm1 2
	CreatePart(Vector4(0.0f, 0.6f, 0.0f, 1.0f), Vector3(2.0f, +0.5f, 0.0f), Vector3(0.5f, 0.4f, 0.5f), _robot[1]);
	//RightArm2 3
	CreatePart(Vector4(0.0f, 0.8f, 0.0f, 1.0f), Vector3(0.0f, -2.5f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), _robot[2]);
	//RightHand 4
	CreatePart(Vector4(0.0f, 1.0f, 0.0f, 1.0f), Vector3(0.0f, -2.0f, 0.0f), Vector3(1.0f, 0.5f, 1.0f), _robot[3]);

	//LeftArm1 5
	CreatePart(Vector4(0.0f, 0.6f, 0.0f, 1.0f), Vector3(-2.0f, +0.5f, 0.0f), Vector3(0.5f, 0.4f, 0.5f), _robot[1]);
	//LeftArm2 6
	CreatePart(Vector4(0.0f, 0.8f, 0.0f, 1.0f), Vector3(-0.0f, -2.5f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), _robot[5]);
	//LeftHand 7
	CreatePart(Vector4(0.0f, 1.0f, 0.0f, 1.0f), Vector3(-0.0f, -2.0f, 0.0f), Vector3(1.0f, 0.5f, 1.0f), _robot[6]);

	//RightLeg1 8
	CreatePart(Vector4(0.0f, 0.6f, 0.0f, 1.0f), Vector3(0.7f, -1.6f, 0.0f), Vector3(0.5f, 0.4f, 0.5f), _robot[1]);
	//RightLeg2 9
	CreatePart(Vector4(0.0f, 0.8f, 0.0f, 1.0f), Vector3(0.0f, -2.5f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), _robot[8]);
	//RightFoot 10
	CreatePart(Vector4(0.0f, 1.0f, 0.0f, 1.0f), Vector3(0.0f, -2.0f, 1.0f), Vector3(1.0f, 0.5f, 2.0f), _robot[9]);

	//LeftLeg1 11
	CreatePart(Vector4(0.0f, 0.6f, 0.0f, 1.0f), Vector3(-0.7f, -1.6f, 0.0f), Vector3(0.5f, 0.4f, 0.5f), _robot[1]);
	//LeftLeg2 12
	CreatePart(Vector4(0.0f, 0.8f, 0.0f, 1.0f), Vector3(-0.0f, -2.5f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), _robot[11]);
	//LeftFoot 13
	CreatePart(Vector4(0.0f, 1.0f, 0.0f, 1.0f), Vector3(-0.0f, -2.0f, 1.0f), Vector3(1.0f, 0.5f, 2.0f), _robot[12]);
}

void Robot::CreatePart(Vector4 color, Vector3 pos, Vector3 scale, Cube* parent)
{
	Cube* part;
	part = new Cube(color);
	part->SetParent(parent);
	part->_translation = pos;
	part->_scale = scale;
	_robot.push_back(part);
}

void Robot::Move()
{
	if (KEY_PRESS(VK_UP))
	{
		_robot[0]->_translation += _robot[0]->Forward() * Time::Delta();

		if (_robot[8]->_rotation.x > 1.0f || _robot[8]->_rotation.x < -1.0f)
			_rightUp = !_rightUp;

		if (_rightUp)
		{
			_robot[8]->_rotation.x += Time::Delta();
			_robot[11]->_rotation.x -= Time::Delta();
			_robot[2]->_rotation.x -= Time::Delta();
			_robot[5]->_rotation.x += Time::Delta();
		}
		else
		{
			_robot[8]->_rotation.x -= Time::Delta();
			_robot[11]->_rotation.x += Time::Delta();
			_robot[2]->_rotation.x += Time::Delta();
			_robot[5]->_rotation.x -= Time::Delta();
		}

	}
	else if (KEY_PRESS(VK_DOWN))
	{
		_robot[0]->_translation += _robot[0]->Backward() * Time::Delta();

		if (_robot[8]->_rotation.x > 1.0f || _robot[8]->_rotation.x < -1.0f)
			_rightUp = !_rightUp;

		if (_rightUp)
		{
			_robot[8]->_rotation.x += Time::Delta();
			_robot[11]->_rotation.x -= Time::Delta();
			_robot[2]->_rotation.x -= Time::Delta();
			_robot[5]->_rotation.x += Time::Delta();
		}
		else
		{
			_robot[8]->_rotation.x -= Time::Delta();
			_robot[11]->_rotation.x += Time::Delta();
			_robot[2]->_rotation.x += Time::Delta();
			_robot[5]->_rotation.x -= Time::Delta();
		}

	}
	else
	{
		_robot[8]->_rotation.x = 0.0f;
		_robot[11]->_rotation.x = 0.0f;
		_robot[2]->_rotation.x = 0.0f;
		_robot[5]->_rotation.x = 0.0f;
	}

	if (KEY_PRESS(VK_LEFT))
		_robot[0]->_rotation.y -= Time::Delta();

	if (KEY_PRESS(VK_RIGHT))
		_robot[0]->_rotation.y += Time::Delta();
}


