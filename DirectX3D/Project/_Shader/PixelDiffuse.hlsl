#include "header.hlsli"

struct VertexOutPut
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float diffuse : DIFFUSE;
};

float4 main(VertexOutPut input) : SV_TARGET
{
	return diffuseMap.Sample(samp, input.uv) * input.diffuse;
}