#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
	_vertexBuffer->Release();
}

void VertexBuffer::IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY type)
{
	DC->IASetPrimitiveTopology(type);
	DC->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
}

void VertexBuffer::UpdateVertex(void* data, UINT count)
{
	DC->UpdateSubresource(_vertexBuffer, 0, nullptr, data, stride, count);
}
