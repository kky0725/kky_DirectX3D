#pragma once
class Cube
{
public:
	Cube();
	~Cube();

	void Update();
	void Render();


private:
	MatrixBuffer* _worldBuffer;

	vector<VertexColor>	vertices;
	vector<UINT>		indices;

	//shader->Material
	VertexShader* _vertexShader;
	PixelShader*  _pixelShader;

	//Vertex, Index -> Mesh
	VertexBuffer* _vertexBuffer;
	IndexBuffer*  _indexBuffer;
};