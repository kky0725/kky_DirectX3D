#pragma once
class Quad : public Transform
{
public:
	Quad(Vector2 size = {1, 1});
	Quad(wstring file);
	virtual ~Quad();

	virtual void Update();
	void Render();

	Material* GetMaterial() { return _material; }

protected:
	Material* _material	= nullptr;
	Mesh*	  _mesh		= nullptr;

	vector<VertexTextureNormal> _vertices;
	vector<UINT>				_indices;

	MatrixBuffer* _worldBuffer = nullptr;
};