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

	ID3D11Device* device;        //무언가를 만들 때 사용, CPU를 다루는 객체
	ID3D11DeviceContext* deviceContext; //무언가를 그릴 때 사용, GPU를 다루는 객체

	IDXGISwapChain* swapChain;          //더블 버퍼링을 구현하는 객체
	ID3D11RenderTargetView* renderTargetView;   //

	/// ///////////////////

	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;

	ID3D11InputLayout* inputLayout;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* constBuffer;

	UINT stride = 0;
	UINT offset = 0;
};

