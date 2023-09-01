#pragma once

struct Vertex
{
	Vertex()
	{}

	Vertex(float x, float y, float z)
	{
		pos = XMFLOAT3(x, y, z);
	}

	XMFLOAT3 pos = {};
};

struct VertexColor
{
	VertexColor()
	{}

	VertexColor(XMFLOAT3 pos, XMFLOAT4 color)
		:pos(pos), color(color)
	{
	}

	XMFLOAT3 pos	= {};
	XMFLOAT4 color	= {};
};

struct VertexTexture
{
	VertexTexture()
	{}

	VertexTexture(XMFLOAT3 pos, XMFLOAT2 uv)
		:pos(pos), uv(uv)
	{
	}

	XMFLOAT3 pos = {};
	XMFLOAT2 uv	 = {};
};

struct VertexTextureNormal
{
	VertexTextureNormal()
	{
	}

	XMFLOAT3 pos = {};
	XMFLOAT2 uv = {};
	Vector3 normal = {};
};