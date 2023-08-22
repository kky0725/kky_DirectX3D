#include "Framework.h"
#include "Cube.h"

Cube::Cube()
{
	_material = new Material(L"Tutorial");

	CreateMesh();

	_worldBuffer = new MatrixBuffer();
}

Cube::~Cube()
{
	delete _mesh;
	delete _material;

	delete _worldBuffer;
}

void Cube::Update()
{
	_S = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	_R = XMMatrixRotationRollPitchYaw(_rotation.x, _rotation.y, _rotation.z);
	_T = XMMatrixTranslation(_translation.x, _translation.y, _translation.z);

	_world = _S * _R * _T;

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

void Cube::CreateMesh()
{
	_vertices =
	{
		VertexColor({ -1.0f, +1.0f, -1.0f }, { 1.0f, 0.0f, 0.0f ,1.0f }),
		VertexColor({ +1.0f, +1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f ,1.0f }),
		VertexColor({ -1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f, 1.0f ,1.0f }),
		VertexColor({ +1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 0.0f ,1.0f }),

		VertexColor({ -1.0f, +1.0f, +1.0f }, { 1.0f, 0.0f, 0.0f ,1.0f }),
		VertexColor({ +1.0f, +1.0f, +1.0f }, { 0.0f, 1.0f, 0.0f ,1.0f }),
		VertexColor({ -1.0f, -1.0f, +1.0f }, { 0.0f, 0.0f, 1.0f ,1.0f }),
		VertexColor({ +1.0f, -1.0f, +1.0f }, { 1.0f, 1.0f, 0.0f ,1.0f })
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
	if (ImGui::BeginMenu("Cube"))
	{
		ImGui::DragFloat3("Scale",		 (float*)&_scale,		0.01f, 0.01f, 100.0f);
		//ImGui::DragFloat3("Rotation",	 (float*)&_rotation,	0.01f, -XM_2PI, +XM_2PI);
		ImGui::SliderAngle("Rotationx", &_rotation.x);//270���� ������ ���� �߻�->���ʹϾ� ������ ����ؼ� �ذ� ����
		ImGui::SliderAngle("Rotationy", &_rotation.y);
		ImGui::SliderAngle("Rotationz", &_rotation.z);
		ImGui::DragFloat3("Translation", (float*)&_translation, 0.01f, -WIN_WIDTH, WIN_WIDTH);

		ImGui::EndMenu();
	}
}

