#include "Framework.h"
#include "ConstBuffer.h"

ConstBuffer::ConstBuffer(void* data, UINT dataSize)
	:_data(data), _dataSize(dataSize)
{
	D3D11_BUFFER_DESC bufferDesc = {};

	bufferDesc.ByteWidth			= dataSize;
	bufferDesc.Usage				= D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags		= 0;
	bufferDesc.MiscFlags			= 0;
	bufferDesc.StructureByteStride	= 0;

	DEVICE->CreateBuffer(&bufferDesc, nullptr, &_constBuffer);
}

ConstBuffer::~ConstBuffer()
{
	_constBuffer->Release();
}

void ConstBuffer::SetVSBuffer(UINT slot)
{
	UpdataeSubresource();

	DC->VSSetConstantBuffers(slot, 1, &_constBuffer);
}

void ConstBuffer::SetPSBuffer(UINT slot)
{
	UpdataeSubresource();

	DC->PSSetConstantBuffers(slot, 1, &_constBuffer);
}

void ConstBuffer::UpdataeSubresource()
{
	DC->UpdateSubresource(_constBuffer, 0, nullptr, _data, 0, 0);
}
