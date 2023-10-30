#include "Framework.h"
#include "ImageCube.h"

int ImageCube::_count = 0;

ImageCube::ImageCube()
{
	_size = 1.0f;
	_count++;
	_ID = "Cube" + to_string(_count);
	CreateFaces();
}

ImageCube::~ImageCube()
{
}

void ImageCube::Update()
{
	Transform::Update();
	for (Quad* face : _faces)
		face->Update();

	Move();
}

void ImageCube::Render()
{
	for (Quad* face : _faces)
		face->Render();
}

void ImageCube::CreateFaces()
{
	//Foward
	CreateFace({ 0.0f, 0.0f, 0.0f }, {0.0f, 0.0f, -_size * 0.5f});

	//Backward
	CreateFace({ XM_PI, 0.0f, 0.0f }, { 0.0f, 0.0f, +_size * 0.5f });

	//Left
	CreateFace({ 0.0f, XM_PIDIV2, 0.0f }, { -_size * 0.5f, 0.0f, 0.0f });

	//Right
	CreateFace({ 0.0f, -XM_PIDIV2, 0.0f }, { +_size * 0.5f, 0.0f, 0.0f });

	//Top
	CreateFace({ XM_PIDIV2, 0.0f, 0.0f }, { 0.0f, +_size * 0.5f, 0.0f });

	//Bottom
	CreateFace({ -XM_PIDIV2, 0.0f, 0.0f }, { 0.0f, -_size * 0.5f, 0.0f });
}

void ImageCube::CreateFace(Vector3 rotation, Vector3 translation)
{
	//Quad* quad = new Quad({ _size, _size });
	//quad->_rotation = rotation;
	//quad->_translation = translation;

	//quad->SetParent(this);
	//_faces.push_back(quad);
}

void ImageCube::Move()
{
	if (KEY_PRESS('W'))
		this->_translation += this->Forward() * Time::Delta();

	if (KEY_PRESS('S'))
		this->_translation += this->Backward() * Time::Delta();

	if (KEY_PRESS('A'))
		this->_translation += this->Left() * Time::Delta();

	if (KEY_PRESS('D'))
		this->_translation += this->Right() * Time::Delta();

	if (KEY_PRESS(VK_UP))
		this->_rotation.x += Time::Delta();

	if (KEY_PRESS(VK_DOWN))
		this->_rotation.x -= Time::Delta();

	if (KEY_PRESS(VK_LEFT))
		this->_rotation.y -= Time::Delta();

	if (KEY_PRESS(VK_RIGHT))
		this->_rotation.y += Time::Delta();
}

void ImageCube::Debug()
{
	if (ImGui::BeginMenu(_ID.c_str()))
	{
		ImGui::DragFloat3("Scale", (float*)&_scale, 0.01f, 0.01f, 100.0f);
		ImGui::SliderAngle("Rotationx", &_rotation.x);//270에서 짐벌락 현상 발생->쿼터니언 각도를 사용해서 해결 가능
		ImGui::SliderAngle("Rotationy", &_rotation.y);
		ImGui::SliderAngle("Rotationz", &_rotation.z);
		ImGui::DragFloat3("Translation", (float*)&_translation, 0.01f, -WIN_WIDTH, WIN_WIDTH);

		ImGui::EndMenu();
	}
}
