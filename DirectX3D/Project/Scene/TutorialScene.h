#pragma once

struct Vertex
{
	Vertex(float x, float y, float z)
	{
		pos = XMFLOAT3(x, y, z);
	}

	XMFLOAT3 pos;
};

struct VertexColor
{
	VertexColor(XMFLOAT3 pos, XMFLOAT4 color)
		:pos(pos), color(color)
	{
	}

	XMFLOAT3 pos;
	XMFLOAT4 color;
};

class TutorialScene : public Scene
{
public:
	TutorialScene();
	virtual ~TutorialScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	MatrixBuffer* _worldBuffer;
	MatrixBuffer* _viewBuffer;
	MatrixBuffer* _projectionBuffer;

	vector<VertexColor>	vertices;
	vector<UINT>		indices;

	/// //////////////////

	VertexShader* _vertexShader;
	 PixelShader* _pixelShader;

	VertexBuffer* _vertexBuffer;
	IndexBuffer* _indexBuffer;

	//ConstBuffer* _constBuffer;

};

