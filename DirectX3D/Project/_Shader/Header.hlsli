cbuffer World : register(b0)
{
	matrix world;
};

cbuffer View : register(b1)
{
	matrix view;
};

cbuffer Projection : register(b2)
{
	matrix projection;
};

cbuffer LightDirection : register(b3)
{
	float3 lightDirection;
};

struct VertexTexture
{
	float4 pos : POSITION;
	float2 uv : UV;
};

struct VertexColor
{
	float4 pos : POSITION;
	float4 color : COLOR;
};

struct VertexTextureNormal
{
	float4 pos : POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
};

Texture2D diffuseMap : register(t0);
SamplerState	samp : register(s0);