#pragma once

struct Vertex
{
	Vertex(float x, float y, float z)
	{
		pos = XMFLOAT3(x, y, z);
	}

	XMFLOAT3 pos;
};

struct VertexColor
{
	VertexColor(XMFLOAT3 pos, XMFLOAT4 color)
		:pos(pos), color(color)
	{
	}

	XMFLOAT3 pos;
	XMFLOAT4 color;
};
