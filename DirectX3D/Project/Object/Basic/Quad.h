#pragma once
class Quad : public Transform
{
public:
	Quad(Vector2 size = {1, 1});
	virtual ~Quad();

	virtual void Update();
	void Render();

private:
	Material* _material	= nullptr;
	Mesh*	  _mesh		= nullptr;

	vector<VertexTexture> _vertices;
	vector<UINT>		   _indices;

	MatrixBuffer* _worldBuffer = nullptr;
};