#pragma once
class Quad : public Transform
{
	typedef VertexTextureNormalTangent VertexType;
public:
	Quad(Vector2 size = {1, 1});
	Quad(wstring file);
	virtual ~Quad();

	virtual void Update();
	void Render();
	void RenderInstanced(UINT instanceCount);

	Material* GetMaterial() { return _material; }

protected:
	Material* _material	= nullptr;
	Mesh*	  _mesh		= nullptr;

	vector<VertexType> _vertices;
	vector<UINT>				_indices;

	MatrixBuffer* _worldBuffer = nullptr;
};