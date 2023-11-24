#include "header.hlsli"

struct VertextOutput
{
	float4 pos			: SV_POSITION;
	float2 uv			: UV;
	float4 reflectPos	: POSITION0;
	float4 refractPos	: POSITION1;
	float4 worldPos		: POSITION2;
};

cbuffer ReflectionBuffer : register(b10)
{
	matrix reflectionView;
}

VertextOutput main(VertexTexture input)
{
	VertextOutput output;
	
	output.pos = mul( input.pos, world);
	
	output.worldPos = output.pos;
	
	output.reflectPos = mul(output.pos, reflectionView);
	output.reflectPos = mul(output.reflectPos, projection);
	
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);
	
	output.uv = input.uv;
	output.reflectPos = output.pos;
	
	return output;
}