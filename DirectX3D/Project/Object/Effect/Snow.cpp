#include "Framework.h"
#include "Snow.h"

Snow::Snow(wstring file)
{
	_material->SetShader(L"17Snow");
	_material->SetDiffuseMap(file);

	_geometryShader = Shader::GetGS(L"17Snow");

	_buffer = new WeatherBuffer();

	SetVertex();
}

Snow::~Snow()
{
	delete _buffer;
}

void Snow::Update()
{
	_buffer->data.time += Time::Delta();
}

void Snow::Render()
{
	_buffer->SetVSBuffer(10);

	Particle::Render();
}

void Snow::Debug()
{
}

void Snow::SetVertex()
{
	_drawCount = MAX_COUNT;

	_vertices.resize(_drawCount);

	for (UINT i = 0; i < _drawCount; i++)
	{
		float size = Random(0.5f, 2.0f);
		_vertices[i].size = {size, size};

		_vertices[i].pos.x = Random(-_buffer->data.size.x, +_buffer->data.size.x);
		_vertices[i].pos.y = Random(-_buffer->data.size.y, +_buffer->data.size.y);
		_vertices[i].pos.z = Random(-_buffer->data.size.z, +_buffer->data.size.z);

		_vertices[i].random.x = Random(0.0f, 1.0f);
		_vertices[i].random.y = Random(0.0f, 1.0f);
	}

	_vertexBuffer = new VertexBuffer(_vertices);
}
