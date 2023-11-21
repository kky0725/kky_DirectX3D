#include "Framework.h"
#include "Rain.h"

Rain::Rain(wstring file)
{
	_material->SetShader(L"16Rain");
	_material->SetDiffuseMap(file);

	_geometryShader = Shader::GetGS(L"16Rain");

	_buffer = new WeatherBuffer();

	SetVertex();
}

Rain::~Rain()
{
	delete _buffer;
}

void Rain::Update()
{
	_buffer->data.time += Time::Delta();
}

void Rain::Render()
{
	_buffer->SetVSBuffer(10);

	Particle::Render();
}

void Rain::Debug()
{
	ImGui::Text("Rain Option");
	ImGui::DragFloat3("Velocity",(float*)&_buffer->data.velocity, 0.1f);
	ImGui::DragFloat ("Distance",(float*)&_buffer->data.distance);//가시 거리
	ImGui::DragFloat ("Turbulence",(float*)&_buffer->data.turblulance, 0.1f, 0.0f, 10.0f);
	ImGui::DragFloat3("Origin",	 (float*)&_buffer->data.origin, 0.1f);
	ImGui::DragFloat3("Size",	 (float*)&_buffer->data.size, 0.1f);
	ImGui::ColorEdit3("Color",	 (float*)&_buffer->data.color, 0.1f);
}

void Rain::SetVertex()
{
	_drawCount = MAX_COUNT;

	_vertices.resize(_drawCount);

	for (UINT i = 0; i < _drawCount; i++)
	{
		Vector2 size;
		size.x = Random(0.1f, 0.4f);
		size.y = Random(4.0f, 8.0f);
		_vertices[i].uv = size;

		Vector3 pos;

		pos.x = Random(-_buffer->data.size.x, +_buffer->data.size.x);
		pos.y = Random(-_buffer->data.size.y, +_buffer->data.size.y);
		pos.z = Random(-_buffer->data.size.z, +_buffer->data.size.z);

		_vertices[i].pos = pos;
	}

	_vertexBuffer = new VertexBuffer(_vertices);
}

