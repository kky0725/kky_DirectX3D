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

struct WVP
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;
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
	WVP wvp;

	vector<VertexColor>	vertices;
	vector<UINT>		indices;

	

	/// ///////////////////



	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* constBuffer;

	UINT stride = 0;
	UINT offset = 0;
};

