#include "header.hlsli"

struct VertexOutPut
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	
	float4 color : COLOR;
};

float4 main(VertexOutPut input) : SV_TARGET
{
	return diffuseMap.Sample(samp, input.uv) * input.color * mDiffuse;
}