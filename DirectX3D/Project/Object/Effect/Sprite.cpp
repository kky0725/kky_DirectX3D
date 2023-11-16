#include "Framework.h"
#include "Sprite.h"

Sprite::Sprite(wstring file, Vector2 size, float frameX, float frameY, bool isAdditive, UINT maxFrameCount)
	:_size(size)
{
	_isAdditive = isAdditive;

	if (maxFrameCount == 0)
		_maxFrameCount = frameX * frameY;
	else
		_maxFrameCount = maxFrameCount;

	_buffer = new FloatValueBuffer();
	_buffer->data.value[0] = frameX;
	_buffer->data.value[1] = frameY;

	_material->SetShader(L"14Sprite");
	_material->SetDiffuseMap(file);

	_geometryShader = Shader::GetGS(L"14Sprite");

	SetVertex();
}

Sprite::~Sprite()
{
	delete _buffer;
}

void Sprite::SetVertex()
{
	_drawCount = 1;

	_vertex.resize(1);

	_vertexBuffer = new VertexBuffer(_vertex);
}

void Sprite::Update()
{
	if (!_isActive)
		return;

	_time += _speed * Time::Delta();

	if (_time > 0.1f)
	{
		_curFrameCount++;

		UINT curFrameX = _curFrameCount % (UINT)_buffer->data.value[0];
		UINT curFrameY = _curFrameCount / (UINT)_buffer->data.value[0];

		_buffer->data.value[2] = curFrameX;
		_buffer->data.value[3] = curFrameY;

		_time = 0.0f;
	}

	if (_curFrameCount >= _maxFrameCount)
		Stop();
}

void Sprite::Render()
{
	_buffer->SetPSBuffer(10);

	Particle::Render();
}

void Sprite::Debug()
{
}

void Sprite::Play(Vector3 position)
{
	_isActive = true;

	_time = 0.0f;
	_curFrameCount = 0.0f;

	_vertex[0].pos = position;
	_vertex[0].uv = _size;

	_vertexBuffer->UpdateVertex(_vertex.data(), _drawCount);
}

