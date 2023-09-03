#include "Header.hlsli"

struct VertexOutPut
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float diffuse : DIFFUSE;
};

VertexOutPut main(VertexColorNormal input)
{
	VertexOutPut output;

	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.color = input.color;
	
	float3 L = normalize(-lightDirection);
	float3 N = normalize(mul(input.normal, (float3x3) world));
	
	output.diffuse = dot(N, L);

	return output;
}