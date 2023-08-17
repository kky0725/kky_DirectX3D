#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(vector<UINT>& indices)
{
	D3D11_BUFFER_DESC bufferDesc = {};

	bufferDesc.ByteWidth = sizeof(UINT) * indices.size();
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;

	data.pSysMem = indices.data();

	DEVICE->CreateBuffer(&bufferDesc, &data, &_indexBuffer);
}

IndexBuffer::~IndexBuffer()
{
	_indexBuffer->Release();
}

void IndexBuffer::IASetBuffer()
{
	DC->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

