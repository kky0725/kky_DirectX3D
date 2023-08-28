#include "Framework.h"
#include "Quad.h"

Quad::Quad(Vector2 size)
{
	float left	 = -size.x * 0.5f;
	float right  = +size.x * 0.5f;
	float bottom = -size.y * 0.5f;
	float top	 = +size.y * 0.5f;

	_vertices =
	{
		{Vector3(left,	top,	0.0f), Vector2(0,0)},
		{Vector3(right, top,	0.0f), Vector2(1,0)},
		{Vector3(left,  bottom, 0.0f), Vector2(0,1)},
		{Vector3(right, bottom, 0.0f), Vector2(1,1)}
	};

	_indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	_mesh = new Mesh(_vertices, _indices);

	_material = new Material();
	_material->SetShader(L"Texture");

	_worldBuffer = new MatrixBuffer();

	//Texture

	ScratchImage image;
	LoadFromWICFile(L"_Texture/Landscape/Box.png", WIC_FLAGS_NONE, nullptr, image);

	CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &_srv);

	D3D11_SAMPLER_DESC samplerDesc = {};

	samplerDesc.Filter			= D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU		= D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV		= D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW		= D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc	= D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD			= 0;
	samplerDesc.MaxLOD			= D3D11_FLOAT32_MAX;

	DEVICE->CreateSamplerState(&samplerDesc, &_samplerState);
}

Quad::~Quad()
{
	delete _mesh;
	delete _worldBuffer;

			 _srv->Release();
	_samplerState->Release();
}

void Quad::Update()
{
	Transform::Update();
}

void Quad::Render()
{
	_worldBuffer->SetData(_world);
	_worldBuffer->SetVSBuffer(0);
	
	_material->SetMaterial();
	_mesh->SetMesh();


	DC->PSSetShaderResources(0, 1, &_srv);
	DC->PSSetSamplers(0, 1, &_samplerState);

	DC->DrawIndexed(_indices.size(), 0, 0);
}
