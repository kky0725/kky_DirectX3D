#include "Header.hlsli"

struct VertexOutPut
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float  diffuse : DIFFUSE;
};

VertexOutPut main(VertexTextureNormal input)
{
	VertexOutPut output;

	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.uv = input.uv;
	
	float3 L = normalize(-lightDirection);
	float3 N = normalize(mul(input.normal, (float3x3) world));
	
	output.diffuse = dot(N, L);

	return output;
}