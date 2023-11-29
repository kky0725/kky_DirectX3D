#include "Framework.h"
#include "ConstBuffer.h"

ConstBuffer::ConstBuffer(void* data, UINT dataSize)
	:_data(data), _dataSize(dataSize)
{
	D3D11_BUFFER_DESC bufferDesc = {};

	bufferDesc.ByteWidth			= dataSize;
	bufferDesc.Usage				= D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
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

void ConstBuffer::SetCSBuffer(UINT slot)
{
	UpdataeSubresource();

	DC->CSSetConstantBuffers(slot, 1, &_constBuffer);
}

void ConstBuffer::SetHSBuffer(UINT slot)
{
	UpdataeSubresource();

	DC->HSSetConstantBuffers(slot, 1, &_constBuffer);
}

void ConstBuffer::SetDSBuffer(UINT slot)
{
	UpdataeSubresource();

	DC->DSSetConstantBuffers(slot, 1, &_constBuffer);
}

void ConstBuffer::UpdataeSubresource()
{
	DC->Map(_constBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_subResource);

	memcpy(_subResource.pData, _data, _dataSize);

	DC->Unmap(_constBuffer, 0);

	//DC->UpdateSubresource(_constBuffer, 0, nullptr, _data, 0, 0);
}
