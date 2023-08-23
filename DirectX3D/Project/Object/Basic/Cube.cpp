#include "Framework.h"
#include "Cube.h"

int Cube::_count = 0;

Cube::Cube(Vector4 color)
{
	_material = new Material(L"Tutorial");

	CreateMesh(color);

	_worldBuffer = new MatrixBuffer();

	_count++;

	_label = "Cube" + to_string(_count);
}

Cube::~Cube()
{
	delete _mesh;
	delete _material;

	delete _worldBuffer;
}

void Cube::Update()
{
	Transform::Update();

	_worldBuffer->SetData(_world);
}

void Cube::Render()
{
	//todo: Render
	_material->SetMaterial();
	_mesh->SetMesh();

	_worldBuffer->SetVSBuffer(0);

	DC->DrawIndexed(_indices.size(), 0, 0);
	
}

void Cube::CreateMesh(Vector4 color)
{
	_vertices =
	{
		VertexColor({ -1.0f, +1.0f, -1.0f }, color),
		VertexColor({ +1.0f, +1.0f, -1.0f }, color),
		VertexColor({ -1.0f, -1.0f, -1.0f }, color),
		VertexColor({ +1.0f, -1.0f, -1.0f }, color),

		VertexColor({ -1.0f, +1.0f, +1.0f }, color),
		VertexColor({ +1.0f, +1.0f, +1.0f }, color),
		VertexColor({ -1.0f, -1.0f, +1.0f }, color),
		VertexColor({ +1.0f, -1.0f, +1.0f }, color)
	};

	_indices =
	{
		//Front
		0, 1, 2,
		2, 1, 3,

		//Right
		1, 5, 3,
		3, 5, 7,

		//Top
		0, 4, 1,
		1, 4, 5,

		//Left
		4, 0, 6,
		6, 0, 2,

		//Back
		5, 4, 7,
		7, 4, 6,

		//Bottom
		2, 3, 6,
		6, 3, 7

	};

	_mesh = new Mesh(_vertices, _indices);
}

void Cube::Debug()
{
	if (ImGui::BeginMenu(_label.c_str()))
	{
		ImGui::DragFloat3("Scale",		 (float*)&_scale,		0.01f, 0.01f, 100.0f);
		//ImGui::DragFloat3("Rotation",	 (float*)&_rotation,	0.01f, -XM_2PI, +XM_2PI);
		ImGui::SliderAngle("Rotationx", &_rotation.x);//270에서 짐벌락 현상 발생->쿼터니언 각도를 사용해서 해결 가능
		ImGui::SliderAngle("Rotationy", &_rotation.y);
		ImGui::SliderAngle("Rotationz", &_rotation.z);
		ImGui::DragFloat3("Translation", (float*)&_translation, 0.01f, -WIN_WIDTH, WIN_WIDTH);

		ImGui::EndMenu();
	}
}

