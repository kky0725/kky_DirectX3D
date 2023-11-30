#pragma once
class Mesh
{
public:
	template <typename T>
	Mesh(vector<T>& vertices);
	template <typename T>
	Mesh(vector<T>& vertices, vector<UINT>& indices);
	~Mesh();

	void SetMesh(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	void UpdateVertex(void* data, UINT count) { _vertexBuffer->UpdateVertex(data, count); }

private:
	VertexBuffer* _vertexBuffer;
	IndexBuffer*  _indexBuffer;
};

template<typename T>
inline Mesh::Mesh(vector<T>& vertices)
{
	_vertexBuffer = new VertexBuffer(vertices);
}

template<typename T>
inline Mesh::Mesh(vector<T>& vertices, vector<UINT>& indices)
{
	_vertexBuffer = new VertexBuffer(vertices);

	if(indices.size() > 0)
		_indexBuffer = new IndexBuffer(indices);
}
