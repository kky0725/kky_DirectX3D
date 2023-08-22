#pragma once
class Cube
{
public:
	Cube();
	~Cube();

	void Update();
	void Render();
	
	void CreateMesh();

	void Debug();

private:
	MatrixBuffer* _worldBuffer;

	vector<VertexColor>	_vertices;
	vector<UINT>		_indices;

	Material* _material;
	Mesh* _mesh;

	//SRT

	XMFLOAT3 _scale			= {1.0f, 1.0f, 1.0f};
	XMFLOAT3 _rotation		= {0.0f, 0.0f, 0.0f};
	XMFLOAT3 _translation	= {0.0f, 0.0f, 0.0f};

	XMMATRIX _S;
	XMMATRIX _R;
	XMMATRIX _T;

	XMMATRIX _world;

};