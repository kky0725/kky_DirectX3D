#pragma once

struct Vector3
{
	Vector3()
	{

	}

	Vector3(float x, float y, float z)	:x(x), y(y), z(z) {}

	Vector3(XMFLOAT3 value)	:x(value.x), y(value.y), z(value.z) {}

	Vector3(XMVECTOR vector)
	{
		x = XMVectorGetX(vector);
		y = XMVectorGetY(vector);
		z = XMVectorGetZ(vector);
	}

	operator XMVECTOR()
	{
		XMVECTOR vector;

		vector = XMVectorSet(x, y, z, 0.0f);

		return vector;
	}

	operator XMFLOAT3()
	{
		return XMFLOAT3(x, y, z);
	}

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};
