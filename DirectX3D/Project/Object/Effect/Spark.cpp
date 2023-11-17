#include "Framework.h"
#include "Spark.h"

Spark::Spark(wstring file, bool isAdditive)
{
	_isAdditive = isAdditive;

	_material->SetShader(L"15Spark");
	_material->SetDiffuseMap(file);

	_geometryShader = Shader::GetGS(L"15Spark");

		 _valueBuffer = new FloatValueBuffer();
	_startColorBuffer = new FloatValueBuffer();
	  _endColorBuffer = new FloatValueBuffer();

	_startColorBuffer->data.value[3] = 1.0f;
	  _endColorBuffer->data.value[3] = 1.0f;

	SetVertex();
}

Spark::~Spark()
{
	delete _valueBuffer;
	delete _startColorBuffer;
	delete _endColorBuffer;
}

void Spark::Update()
{
	if (!_isActive)
		return;

	//value0 : time
	//value1 : duration
	_valueBuffer->data.value[0] += Time::Delta();

	if (_valueBuffer->data.value[0] > _valueBuffer->data.value[1])
		Stop();
}

void Spark::Render()
{
		 _valueBuffer->SetVSBuffer(10);
		 _valueBuffer->SetPSBuffer(10);
	_startColorBuffer->SetPSBuffer(11);
	  _endColorBuffer->SetPSBuffer(12);

	  Particle::Render();
}

void Spark::Debug()
{
	ImGui::Text("Spark Option");

	ImGui::SliderInt("Particle Count", (int*)&_drawCount, 1, MAX_COUNT);

	ImGui::ColorEdit4("StartColor", _startColorBuffer->data.value);
	ImGui::ColorEdit4("EndColor", _endColorBuffer->data.value);
}

void Spark::Play(Vector3 position)
{
	_valueBuffer->data.value[0] = 0.0f;

	Particle::Play(position);

	UpdateParticle();
	_vertexBuffer->UpdateVertex(_vertices.data(), _drawCount);
}

void Spark::SetVertex()
{
	_vertices.resize(MAX_COUNT);

	_vertexBuffer = new VertexBuffer(_vertices);

	_drawCount = 500;

	_valueBuffer->data.value[1] = 1.0f;
}

void Spark::UpdateParticle()
{
	for (UINT i = 0; i < _drawCount; i++)
	{
		_vertices[i].position = _postition;

		float size = Random(_minSize, _maxSize);

		_vertices[i].size = { size, size };

		Vector3 rot;
		rot.x = Random(0.0f, XM_2PI);
		rot.y = Random(0.0f, XM_2PI);
		rot.z = Random(0.0f, XM_2PI);

		float radius = Random(_minRadius, _maxRaidus);

		Vector3 velocity = Vector3(0, 0, radius);

		Matrix rotMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);

		_vertices[i].velocity = XMVector3TransformCoord(velocity, rotMatrix);
	}
}

