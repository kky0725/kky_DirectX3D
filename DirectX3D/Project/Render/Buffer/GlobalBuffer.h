#pragma once

class MatrixBuffer : public ConstBuffer
{
public:
	MatrixBuffer()
		:ConstBuffer(&data, sizeof(data))
	{
		data.matrix = XMMatrixIdentity();
	}
	
	void SetData(XMMATRIX value)
	{
		data.matrix = XMMatrixTranspose(value);
	}

private:
	struct Data
	{
		XMMATRIX matrix;
	} data;
};

class LightBuffer : public ConstBuffer
{
public:
	LightBuffer()
		:ConstBuffer(&data, sizeof(data))
	{
		data.direction = V_DOWN;
	}

	void SetData(Vector3 direction)
	{
		data.direction = direction;
	}

private:
	struct Data
	{
		Vector3 direction;

		float padding;
	} data;
};

class ViewBuffer : public ConstBuffer
{
public:
	ViewBuffer()
		:ConstBuffer(&data, sizeof(Data))
	{
		data.view = XMMatrixIdentity();;
		data.invView = XMMatrixIdentity();
	}

	void SetData(XMMATRIX view, XMMATRIX invView)
	{
		data.view = XMMatrixTranspose(view);
		data.invView = XMMatrixTranspose(invView);
	}

private:
	struct Data
	{
		XMMATRIX view;
		XMMATRIX invView;
	} data;
};